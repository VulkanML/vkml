#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/OwningOpRef.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Support/LLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdlib>
#include <string>
#include <utility>

int main(int argc, char** argv) {
 
    mlir::registerCanonicalizerPass();

    mlir::DialectRegistry registry;
    return mlir::asMainReturnCode(mlir::MlirOptMain(
        argc, argv, "Minimal Standalone optimizer driver\n", registry));
}