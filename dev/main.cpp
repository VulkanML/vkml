#include "vkml.h"
#include <fstream>

//
//using namespace mlir;
//using namespace llvm;

int main() {
	vkml::tensor<float> t1({ 10, 200, 120, 1 });
	vkml::tensor<float> t2({ 10, 1024, 120, 1 });
	auto t3 = vkml::abs(t1);
	compile_module();
	return 0;
}


/*
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
		mlir::Value{}, /*dynamicSharedMemorySize
		main_func_op.getArguments()
	);



	main_func_builder.create<func::ReturnOp>(main_func_builder.getUnknownLoc());
	mod.push_back(main_func_op);
	mod.push_back(gpu_mod);
	//mod.dump();
	auto mod2 = vkml::runMLirPasses(mod);
	mod.dump();

	printf("\n\n......\n\n");
	
	std::vector<llvm::SmallVector<uint32_t, 0>> binary_groups;
	mod->walk([&](mlir::Operation* op) {
		auto spirv_mod = dyn_cast_or_null<spirv::ModuleOp> (op);
		llvm::SmallVector<uint32_t, 0> bin;
		if (spirv_mod != nullptr)
		{
			spirv::serialize(spirv_mod, bin);
			binary_groups.push_back(bin);
		}
	});
	

	std::ofstream output_file("./example.txt");
	std::ostream_iterator<uint32_t> output_iterator(output_file, "");
	std::copy(binary_groups[0].begin(), binary_groups[0].end(), output_iterator);
	output_file.flush();
	
	auto mod22 = spirv::deserialize(binary_groups[0], &ctx);
	mod22->dump();

	return 0;
static spirv::TargetEnvAttr registerTargetEnv(MLIRContext* ctx) {
		Builder builder(ctx);

		auto ver = spirv::VerCapExtAttr::get(
			spirv::Version::V_1_6,
			{
				spirv::Capability::Shader,
			},
			{
			   spirv::Extension::SPV_KHR_storage_buffer_storage_class,
			   spirv::Extension::SPV_KHR_cooperative_matrix,
			   spirv::Extension::SPV_KHR_8bit_storage,
			   spirv::Extension::SPV_KHR_16bit_storage
			},
			ctx);

		int max_compute_shared_memory_size = 1024;
		int max_compute_workgroup_invocations = 1024;

		llvm::SmallVector<Attribute> max_compute_workgroup_size;
		for (auto i : { 1024, 1024, 64 })
			max_compute_workgroup_size.push_back(builder.getI32IntegerAttr(i));

		int subgroup_size = 64;
		int min_subgroup_size = 32;
		int max_subgroup_size = 128;

		auto cooperative_matrix_properties_khr = ArrayAttr::get(ctx, {});
		auto cooperative_matrix_properties_nv = ArrayAttr::get(ctx, {});

		auto resource = spirv::ResourceLimitsAttr::get(ctx,
			max_compute_shared_memory_size,
			max_compute_workgroup_invocations,
			builder.getArrayAttr(max_compute_workgroup_size),
			subgroup_size,
			min_subgroup_size,
			max_subgroup_size,
			cooperative_matrix_properties_khr,
			cooperative_matrix_properties_nv
		);

		return spirv::TargetEnvAttr::get(
			ver,
			resource,
			spirv::ClientAPI::Vulkan,
			spirv::Vendor::NVIDIA,
			spirv::DeviceType::DiscreteGPU,
			0);
	}




*/