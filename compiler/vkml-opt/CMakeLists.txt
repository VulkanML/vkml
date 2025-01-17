
add_llvm_executable(vkml-opt vkml-opt.cpp)
llvm_update_compile_flags(vkml-opt)
add_dependencies(vkml-opt vkml_mlir_compiler)
target_include_directories(vkml-translate PRIVATE ${COMPILER_INCLUDE_DIRS})

set(LIBS vkml_mlir_compiler
	MLIRDebug
	MLIROptLib
	vkml_mlir_compiler
)
target_link_libraries(vkml-opt PRIVATE ${LIBS})
