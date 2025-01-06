#include "vkml_compiler.h"


int main() {
	auto ctx = generateBase();
	auto target = vkml::registerTargetEnv(&ctx, {}, {});
	mlir::Builder builder(&ctx);
	auto module = mlir::ModuleOp::create(builder.getUnknownLoc());	
	module.dump();
	return 0;	
}