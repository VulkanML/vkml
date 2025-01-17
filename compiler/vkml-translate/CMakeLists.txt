set(LLVM_LINK_COMPONENTS
  Support
  )

add_llvm_executable(vkml-translate vkml-translate.cpp)
llvm_update_compile_flags(vkml-translate)
add_dependencies(vkml-translate vkml_mlir_compiler)
target_include_directories(vkml-translate PRIVATE ${COMPILER_INCLUDE_DIRS})
target_link_libraries(vkml-translate PRIVATE 
	MLIRTranslateLib
	vkml_mlir_compiler 
)