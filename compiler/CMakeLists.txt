
set(TARGET_NAME vkml_mlir_compiler)
set(TBLEGEN_TARGET_NAME "${TARGET_NAME}_tblgen")
set(STATIC_TARGET_NAME "${TARGET_NAME}_static")

# file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "*.cpp" "*.h" "*.hpp")
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})


execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-decls --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlDialect.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-defs --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlDialect.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlTypes.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlTypes.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlOps.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlOps.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)


# target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# set(LLVM_TARGET_DEFINITIONS vkmlOps.td)
# mlir_tablegen(VKMLOps.h.inc -gen-op-decls)
# mlir_tablegen(VKMLOps.cpp.inc -gen-op-defs)
# mlir_tablegen(VKMLDialect.h.inc -gen-dialect-decls -dialect=vkml)
# mlir_tablegen(VKMLDialect.cpp.inc -gen-dialect-defs -dialect=vkml)
# add_public_tablegen_target(MLIRVKMLOpsIncGen)
# add_dependencies(mlir-headers MLIRVKMLOpsIncGen)

# set(LLVM_TARGET_DEFINITIONS vkmlTypes.td)
# mlir_tablegen(VKMLTypes.h.inc -gen-typedef-decls)mlir_tablegen(VKMLTypes.cpp.inc -gen-typedef-defs)
# add_public_tablegen_target(MLIRVKMLTypesIncGen)