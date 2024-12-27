set(LLVM_LINK_COMPONENTS Support)


set(LIBS
  MLIRParser
  MLIRSupport
  MLIRIR
)

add_mlir_tool(vkml-opt vkml-opt.cpp PARTIAL_SOURCES_INTENDED DEPENDS ${LIBS})

target_link_libraries(vkml-opt PRIVATE ${LIBS})
llvm_update_compile_flags(vkml-opt)
mlir_check_all_link_libraries(vkml-opt)

