
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




def VKML_Add_Op : VKML_Op<"add"> {
    let summary = "Add two integers";
    let description = [{
        Add two integers.
    }];
    let arguments = (ins
        Arg<AnyMemRef, "", [MemReadAt<0, FullEffect>]> :$lhs,
        Arg<AnyMemRef, "", [MemReadAt<0, FullEffect>]> :$rhs
    );
    let results = (outs
        Arg<AnyMemRef, "", [MemWriteAt<0, FullEffect>]>:$result
    );

    
}

#endif // VKML_OPS