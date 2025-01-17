#include "vkml.h"


using namespace mlir;
using namespace llvm;

int main() {
	MLIRContext ctx;
	auto mod = vkml::initalize(ctx);
	auto gpu_mod = vkml::createGpuModule(mod);

	OpBuilder gpu_builder(&gpu_mod.getBodyRegion());
	
	auto memrefType = MemRefType::get(8, gpu_builder.getF32Type());
	
	auto funcOp = gpu_builder.create<gpu::GPUFuncOp>(gpu_builder.getUnknownLoc(), "kernel_add",
		gpu_builder.getFunctionType({ memrefType, memrefType, memrefType }, {}));

	funcOp->setAttr(spirv::getEntryPointABIAttrName(), 
	spirv::EntryPointABIAttr::get(&ctx, gpu_builder.getDenseI32ArrayAttr({ 1, 1, 1 }), std::nullopt, std::nullopt) );
	
	funcOp->setAttr(gpu::GPUDialect::getKernelFuncAttrName(), gpu_builder.getUnitAttr());

	OpBuilder func_builder(funcOp.getBody());
	auto idx = func_builder.create<gpu::GlobalIdOp>(gpu_builder.getUnknownLoc(), gpu::Dimension::x);
	
	auto func_args = funcOp.getArguments();
	auto i1 = func_builder.create<memref::LoadOp>(func_builder.getUnknownLoc(), func_args[0], ValueRange{ idx });
	auto i2 = func_builder.create<memref::LoadOp>(func_builder.getUnknownLoc(), func_args[1], ValueRange{ idx });
	auto op = func_builder.create<arith::AddFOp>(func_builder.getUnknownLoc(), i1, i2);
	func_builder.create<memref::StoreOp>(func_builder.getUnknownLoc(), op, func_args[2], ValueRange{ idx });
	func_builder.create<gpu::ReturnOp>(func_builder.getUnknownLoc());

	
	OpBuilder builder(mod.getContext());
	auto main_func_op = builder.create<func::FuncOp>(builder.getUnknownLoc(), "main_add",
		builder.getFunctionType({memrefType, memrefType, memrefType}, {}));
	auto entry = main_func_op.addEntryBlock();
	auto args = main_func_op.getArguments();
	auto main_func_builder = OpBuilder(main_func_op.getBody());	
	
	auto const_1 = main_func_builder.create<arith::ConstantIndexOp>(main_func_builder.getUnknownLoc(), 1);
	auto const_8 = main_func_builder.create<arith::ConstantIndexOp>(main_func_builder.getUnknownLoc(),  8);
	auto dynamicSharedMemorySize = main_func_builder.create<arith::ConstantIntOp>(main_func_builder.getUnknownLoc(), 256, 32);
	
	gpu::KernelDim3 grid_size{ const_1, const_1, const_1 };
	gpu::KernelDim3 cluster_size{ const_1, const_1, const_1 };
	gpu::KernelDim3 block_size{ const_1, const_1, const_1 };

	// for (auto arg : main_func_op.getArguments()) {
	// 	auto t = main_func_builder.create<memref::AllocOp>(main_func_builder.getUnknownLoc(), memrefType);
	// 	args.push_back(arg);
	// }
	
	auto t0 = args[0];
	auto t1 = args[1];
	auto t2 = args[2];

	auto gpu_launch_func = main_func_builder.create<gpu::LaunchFuncOp>(
		main_func_builder.getUnknownLoc(),
		funcOp,
		grid_size, // grid_size in (%cst1, %cst1, %cst1)
		block_size, // block_size in (%cst8, %cst1, %cst1)
		mlir::Value{}, /*dynamicSharedMemorySize*/
		main_func_op.getArguments()
	);



	main_func_builder.create<func::ReturnOp>(main_func_builder.getUnknownLoc());
	mod.push_back(main_func_op);
	mod.push_back(gpu_mod);
	mod.dump();

	printf("\n\n......\n\n");
	auto mod2 = vkml::runMLirPasses(mod);
	mod.dump();
	return 0;
}