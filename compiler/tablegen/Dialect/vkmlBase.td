#ifndef VKML_BASE
#define VKML_BASE


include "mlir/IR/OpBase.td"
include "mlir/Dialect/GPU/IR/GPUBase.td"

def VKML_Dialect : Dialect {
    let name = "vkml";
    let cppNamespace = "::vkml";
    let dependentDialects = ["gpu::GPUDialect"];
}

class VKMLOpTrait<string name> : NativeOpTrait<""> {
  let trait = name;
  let cppNamespace = "::vkml::OpTrait";
}

#endif // VKML_BASE