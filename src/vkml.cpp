// vkml.cpp : Defines the entry point for the application.
//

#include "vkml.h"
#include "mlir/Dialect/SPIRV/SPIRVDialect.h"
#include "mlir/Dialect/SPIRV/SPIRVPasses.h"


void registerDialects(mlir::DialectRegistry &registry)
{
     registry.insert<mlir::spirv::SPIRVDialect>();
}


using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}
