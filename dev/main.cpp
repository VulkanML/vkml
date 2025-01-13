#include "vkml.h"


using namespace mlir;
using namespace llvm;

int main() {
	MLIRContext ctx;
	auto mod = vkml::initalize(ctx);
	auto gpu_mod = vkml::createGpuModule(mod);

	OpBuilder gpu_builder(&gpu_mod.getBodyRegion());

	auto memrefType = MemRefType::get(8, FloatType::getF32(&ctx));
	
	auto funcOp = gpu_builder.create<gpu::GPUFuncOp>(gpu_builder.getUnknownLoc(), "kernel_add",
		gpu_builder.getFunctionType({ memrefType, memrefType, memrefType }, {}));

	funcOp->setAttr(spirv::getEntryPointABIAttrName(), 
	spirv::EntryPointABIAttr::get(&ctx, gpu_builder.getDenseI32ArrayAttr({ 1, 1, 1 }), 0, 32) );
	funcOp->setAttr(gpu::GPUDialect::getKernelFuncAttrName(), gpu_builder.getUnitAttr());
	OpBuilder func_builder(funcOp.getBody());
	auto blockId_x = func_builder.create<gpu::BlockIdOp>(gpu_builder.getUnknownLoc(), gpu::Dimension::x);
	auto blockId_y = func_builder.create<gpu::BlockIdOp>(gpu_builder.getUnknownLoc(), gpu::Dimension::y);
	auto blockId_z = func_builder.create<gpu::BlockIdOp>(gpu_builder.getUnknownLoc(), gpu::Dimension::z);
	func_builder.create<gpu::ReturnOp>(func_builder.getUnknownLoc());

	
	OpBuilder builder(mod.getContext());
	auto main_func_op = builder.create<func::FuncOp>(builder.getUnknownLoc(), "main", builder.getFunctionType({}, {}));
	auto entry = main_func_op.addEntryBlock();
	auto main_func_builder = OpBuilder(main_func_op.getBody());	
	
	auto const_1 = main_func_builder.create<arith::ConstantIndexOp>(main_func_builder.getUnknownLoc(), 1);
	auto const_8 = main_func_builder.create<arith::ConstantIndexOp>(main_func_builder.getUnknownLoc(),  8);
	auto dynamicSharedMemorySize = main_func_builder.create<arith::ConstantIntOp>(main_func_builder.getUnknownLoc(), 256, 32);
	
	gpu::KernelDim3 grid_size{ const_1, const_1, const_1 };
	gpu::KernelDim3 cluster_size{ const_1, const_1, const_1 };
	gpu::KernelDim3 block_size{ const_8, const_1, const_1 };
	SmallVector<mlir::Value> args;
	for (auto arg : funcOp.getArguments()) {
		auto t = main_func_builder.create<memref::AllocOp>(main_func_builder.getUnknownLoc(), memrefType);
		args.push_back(t);
	}
	
	auto gpu_launch_func = main_func_builder.create<gpu::LaunchFuncOp>(
		main_func_builder.getUnknownLoc(),
		funcOp,
		grid_size, // grid_size in (%cst1, %cst1, %cst1)
		block_size, // block_size in (%cst8, %cst1, %cst1)
		mlir::Value{}, /*dynamicSharedMemorySize*/
		ValueRange(args) // arguments
	);
	
	main_func_builder.create<func::ReturnOp>(main_func_builder.getUnknownLoc());
	mod.push_back(main_func_op);

	auto mod2 = vkml::runMLirPasses(mod);
	if(mod2 != nullptr)
		mlir::dyn_cast<mlir::ModuleOp>(mod2).dump();
	printf("\n");
	mod.dump();
	return 0;
}