
add_llvm_executable(vkml-opt main.cpp)
llvm_update_compile_flags(vkml-opt)
add_dependencies(vkml-opt vkml_mlir_compiler)
target_include_directories(vkml-opt PRIVATE ../include)

set(LIBS vkml_mlir_compiler
	MLIRDebug
	MLIROptLib
	vkml_mlir_compiler
)
target_link_libraries(vkml-opt PRIVATE ${LIBS})
