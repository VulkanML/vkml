
#ifndef VKML_OPS
#define VKML_OPS

include "Dialect/vkmlBase.td"
include "mlir/IR/BuiltinAttributes.td"
include "mlir/IR/OpAsmInterface.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/CastInterfaces.td"
include "mlir/Interfaces/ControlFlowInterfaces.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"


class VKML_Op<string mnemonic, list<Trait> traits = []>
    : Op<VKML_Dialect, mnemonic, traits> {

}




#endif // VKML_OPS