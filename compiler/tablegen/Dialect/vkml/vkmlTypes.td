
#ifndef VKML_TYPES
#define VKML_TYPES

include "mlir/IR/AttrTypeBase.td"
include "mlir/IR/DialectBase.td"
include "Dialect/vkmlBase.td"

//===----------------------------------------------------------------------===//
// Type defs
//===----------------------------------------------------------------------===//

class VKML_Type<string name, string typeMnemonic,
                 string baseCppClass = "::mlir::Type">
    : TypeDef<VKML_Dialect, name, [], baseCppClass> {
  let mnemonic = typeMnemonic;
}


class VKML_AnyTensorType<string name, string typeMnemonic>
    : VKML_Type<name, typeMnemonic, "::vkml::BaseTensorType">
    {
    let parameters = (ins
        "::llvm::ArrayRef<int64_t>": $Sizes,
        "::mlir::Type": $DType,
        "Attribute" :$optionalSparsity
    );

    let builders = [
        TypeBuilder<(ins "::llvm::ArraryRef<int64_t>": $Sizes, "::mlir::Type": $DType, "Attribute": $optionalSparsity), 
        [{
            return $_get(context, $Sizes, $DType, $optionalSparsity);
        }]>
    ];

}

#endif // VKML_TYPES 