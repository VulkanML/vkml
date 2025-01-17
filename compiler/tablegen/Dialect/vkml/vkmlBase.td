#ifndef VKML_BASE
#define VKML_BASE


include "mlir/IR/OpBase.td"
include "mlir/Dialect/Arith/IR/ArithBase.td"
include "mlir/Dialect/GPU/IR/GPUBase.td"
include "mlir/Dialect/MemRef/IR/MemRefBase.td"


def VKML_Dialect : Dialect {
    let name = "vkml";
    let cppNamespace = "vkml";
    let dependentDialects = ["gpu::GPUDialect", "memref::MemRefDialect", "arith::ArithDialect"];
}

class VKMLOpTrait<string name> : NativeOpTrait<""> {
  let trait = name;
  let cppNamespace = "::vkml::OpTrait";
}

#endif // VKML_BASE