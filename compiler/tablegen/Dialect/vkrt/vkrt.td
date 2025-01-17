#ifndef VKML_BASE
#define VKML_BASE


include "mlir/IR/OpBase.td"
include "mlir/Dialect/SPIRV/IR/SPIRVOpsBase.td"

def VKRT_Dialect : Dialect {
    let name = "vkml";
    let cppNamespace = "vkml";
    let dependentDialects = ["spirv::SPIRVDialect"];
}

class VKMLOpTrait<string name> : NativeOpTrait<""> {
  let trait = name;
  let cppNamespace = "::vkml::OpTrait";
}

#endif // VKML_BASE