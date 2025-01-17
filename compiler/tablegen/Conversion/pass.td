include "mlir/Pass/PassBase.td"


def VKMLConversionPass : Pass<"VKMLConversionPass", "VKML Conversion Pass"> {
  let summary = "VKML Conversion Pass";
  let description = [{
    This pass converts the VKML dialect to the VKRT dialect.
  }];
}
