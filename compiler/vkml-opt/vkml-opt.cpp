#include "../include/compiler.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/IR/DialectRegistry.h"
#include <mlir/Tools/mlir-opt/MlirOptMain.h>

int main(int argc, char** argv) {
	mlir::DialectRegistry registry;
	mlir::registerCanonicalizerPass();
	return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "VKML Optimizer driver\n", registry));
}