#pragma warning( disable : 4244 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4834 )
#pragma warning( disable : 4146 )

#include <mlir/Support/LLVM.h>

#include <mlir/Pass/Pass.h>
#include <mlir/Pass/PassManager.h>
#include <mlir/Pass/PassOptions.h>

#include <mlir/IR/Types.h>
#include <mlir/IR/DialectRegistry.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/Dialect.h>
#include <mlir/IR/OperationSupport.h>

#include <mlir/Dialect/MemRef/IR/MemRef.h>
#include <mlir/Dialect/Arith/IR/Arith.h>
#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/GPU/IR/GPUDialect.h>
#include <mlir/Dialect/SPIRV/IR/SPIRVDialect.h>
#include <mlir/Dialect/SPIRV/Transforms/Passes.h>
#include <mlir/Dialect/SPIRV/IR/TargetAndABI.h>
#include <mlir/Dialect/SPIRV/IR/SPIRVOps.h>
#include <mlir/Dialect/GPU/Transforms/Passes.h>

#include <mlir/Target/SPIRV/Target.h>

#include <mlir/Conversion/Passes.h>


namespace vkml {
    using namespace mlir;

    static Operation* runMLirPasses(Operation* op) {
        auto module = dyn_cast<ModuleOp>(op);
        if (!module)
            return nullptr;
        PassManager pm(op->getContext());
        
        pm.addPass(createGpuKernelOutliningPass());
        

        pm.addPass(createGpuSPIRVAttachTarget());
        pm.addPass(createConvertToSPIRVPass());

        OpPassManager& spirvModulePM =
            pm.nest<gpu::GPUModuleOp>().nest<spirv::ModuleOp>();
        spirvModulePM.addPass(spirv::createSPIRVLowerABIAttributesPass());
        spirvModulePM.addPass(spirv::createSPIRVUpdateVCEPass());
        
        pm.addPass(createGpuModuleToBinaryPass());
        pm.addPass(createConvertGpuLaunchFuncToVulkanLaunchFuncPass());
        // pm.addPass(spirv::createSPIRVLowerABIAttributesPass());
        //pm.addPass(createConvertVulkanLaunchFuncToVulkanCallsPass());


        pm.run(module);
        return module.getOperation();
    }

    static spirv::TargetEnvAttr registerTargetEnv(MLIRContext* ctx,
        const llvm::SmallVector<spirv::Extension>& extensions,
        const llvm::SmallVector<spirv::Capability>& capabilities) {
        Builder builder(ctx);

        auto ver = spirv::VerCapExtAttr::get(
            spirv::Version::V_1_6,
            capabilities,
            extensions,
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
            spirv::Vendor::Unknown,
            spirv::DeviceType::DiscreteGPU,
            0);
    }



	inline ModuleOp initalize(MLIRContext& ctx) {
        spirv::registerSPIRVTargetInterfaceExternalModels(ctx);
        ctx.loadDialect<gpu::GPUDialect, func::FuncDialect, arith::ArithDialect, memref::MemRefDialect, spirv::SPIRVDialect>();
        OpBuilder builder(&ctx);
        auto mod = builder.create<ModuleOp>(builder.getUnknownLoc());
        mod->setAttr(gpu::GPUDialect::getContainerModuleAttrName(), builder.getUnitAttr());
        auto targetAttr = vkml::registerTargetEnv(&ctx,
        {
            spirv::Extension::SPV_KHR_storage_buffer_storage_class,
            spirv::Extension::SPV_KHR_cooperative_matrix,
            spirv::Extension::SPV_KHR_8bit_storage,
            spirv::Extension::SPV_KHR_16bit_storage
        },
        {
            spirv::Capability::Shader,
            spirv::Capability::CooperativeMatrixKHR,
            spirv::Capability::Float16,
            spirv::Capability::Float64,
            spirv::Capability::Int8,
            spirv::Capability::Int16,
			spirv::Capability::Int64,
            spirv::Capability::StorageUniform16,
            spirv::Capability::StorageBuffer8BitAccess,
            spirv::Capability::Float16Buffer
        });

        mod->setAttr(spirv::getTargetEnvAttrName(), targetAttr);
        return mod;
	}

	inline gpu::GPUModuleOp createGpuModule(ModuleOp mod) {
		OpBuilder builder(mod.getContext());
		auto gpu_mod = builder.create<gpu::GPUModuleOp>(builder.getUnknownLoc(), "kernels");
		mod.push_back(gpu_mod);
		return gpu_mod;
	}



}


//#include "vkmlDialect.h.inc"  
//#include "vkmlTypes.h.inc"

