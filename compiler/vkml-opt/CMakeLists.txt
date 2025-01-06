
add_executable(vkml-opt main.cpp)
add_dependencies(vkml-opt vkml_mlir_compiler_static)
target_include_directories(vkml-opt PRIVATE ../include)
target_include_directories(vkml-opt PRIVATE ${COMPILER_INCLUDE_DIRS})
target_link_libraries(vkml-opt PRIVATE vkml_mlir_compiler_static
	${LLVM_LIB_DIR}/MLIRDebug.lib
	${LLVM_LIB_DIR}/MLIROptLib.lib 
	${LLVM_LIB_DIR}/MLIRMlirOptMain.lib 
	${LLVM_LIB_DIR}/MLIRIRDL.lib
)