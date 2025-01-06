#pragma warning( disable : 4244 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4834 )
#pragma warning( disable : 4146 )

#include <mlir/Support/LLVM.h>

#include <mlir/Pass/Pass.h>
#include <mlir/Pass/PassManager.h>

#include <mlir/IR/Types.h>
#include <mlir/IR/DialectRegistry.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/Dialect.h>

//#include <mlir/Dialect/MemRef/IR/MemRef.h>
//#include <mlir/Dialect/Arith/IR/Arith.h>
//#include <mlir/Dialect/SCF/IR/SCF.h>
//#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/GPU/IR/GPUDialect.h>
#include <mlir/Dialect/SPIRV/IR/SPIRVDialect.h>
#include <mlir/Dialect/SPIRV/Transforms/Passes.h>

#include <mlir/Conversion/GPUToVulkan/ConvertGPUToVulkanPass.h>
#include <mlir/Conversion/GPUToSPIRV/GPUToSPIRVPass.h>
//#include <mlir/Conversion/MemRefToSPIRV/MemRefToSPIRVPass.h>
#include <mlir/Target/SPIRV/Target.h>

namespace vkml {

    static void runMLirPasses(mlir::Operation* op) {
        auto module = mlir::dyn_cast<mlir::ModuleOp>(op);
        if (!module)
            return;
        mlir::PassManager pm(module->getContext());
        if (failed(mlir::applyPassManagerCLOptions(pm))) {
            return;
        }

        pm.addPass(mlir::createConvertGpuLaunchFuncToVulkanLaunchFuncPass());
        pm.addPass(mlir::createConvertGPUToSPIRVPass(true));
        pm.addPass(mlir::createConvertVulkanLaunchFuncToVulkanCallsPass());
        pm.run(module);
    }

    static void registerDialects(mlir::DialectRegistry& registry) {

        mlir::spirv::registerSPIRVTargetInterfaceExternalModels(registry);
        
    }

    static mlir::spirv::TargetEnvAttr registerTargetEnv(mlir::MLIRContext* ctx,
        const llvm::SmallVector<mlir::spirv::Extension>& extensions,
        const llvm::SmallVector<mlir::spirv::Capability>& capabilities) {
        mlir::Builder builder(ctx);

        auto ver = mlir::spirv::VerCapExtAttr::get(
            mlir::spirv::Version::V_1_6,
            capabilities,
            extensions,
            ctx);

        int max_compute_shared_memory_size = 1024;
        int max_compute_workgroup_invocations = 1024;

        llvm::SmallVector<mlir::Attribute> max_compute_workgroup_size;
        for (auto i : { 1024, 1024, 64 })
            max_compute_workgroup_size.push_back(builder.getI32IntegerAttr(i));

        int subgroup_size = 64;
        int min_subgroup_size = 32;
        int max_subgroup_size = 128;

        auto cooperative_matrix_properties_khr = mlir::ArrayAttr::get(ctx, {});
        auto cooperative_matrix_properties_nv = mlir::ArrayAttr::get(ctx, {});

        auto resource = mlir::spirv::ResourceLimitsAttr::get(ctx,
            max_compute_shared_memory_size,
            max_compute_workgroup_invocations,
            builder.getArrayAttr(max_compute_workgroup_size),
            subgroup_size,
            min_subgroup_size,
            max_subgroup_size,
            cooperative_matrix_properties_khr,
            cooperative_matrix_properties_nv
        );

        return mlir::spirv::TargetEnvAttr::get(
            ver,
            resource,
            mlir::spirv::ClientAPI::Vulkan,
            mlir::spirv::Vendor::Unknown,
            mlir::spirv::DeviceType::DiscreteGPU,
            0);
    }

    inline void registerAllPasses() {
        mlir::spirv::registerSPIRVPasses();
    }
}

mlir::MLIRContext generateBase() {
    mlir::DialectRegistry reg;
    reg.insert<
        mlir::gpu::GPUDialect,
        mlir::spirv::SPIRVDialect
    >();
    return mlir::MLIRContext(reg, mlir::MLIRContext::Threading::ENABLED);
}


//#include "vkmlDialect.h.inc"
//#include "vkmlTypes.h.inc"

