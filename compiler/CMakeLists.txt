
set(TARGET_NAME vkml_mlir_compiler)
set(TBLEGEN_TARGET_NAME "${TARGET_NAME}_tblgen")
set(STATIC_TARGET_NAME "${TARGET_NAME}_static")

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-decls --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlDialect.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-defs --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlDialect.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlTypes.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlTypes.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlOps.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlOps.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)


file(GLOB_RECURSE COMP_SOURCES CONFIGURE_DEPENDS "*.cpp" )
file(GLOB_RECURSE COMP_HEADERS CONFIGURE_DEPENDS "*.h" "*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${COMP_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${COMP_HEADERS})


get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)
get_property(translation_libs GLOBAL PROPERTY MLIR_TRANSLATION_LIBS)



add_mlir_aggregate(${TARGET_NAME}
    STATIC
    ${COMP_SOURCES} ${COMP_HEADERS}
    PUBLIC_LIBS
    MLIRIR
    MLIRParser
    MLIRPass
    MLIRSupport
    MLIRTransforms
    

    MLIRArithDialect
    MLIRGPUDialect
    MLIRGPUTransforms
    MLIRFuncDialect
    MLIRMemRefDialect
    MLIRSPIRVDialect
    MLIRSPIRVTarget
    MLIRSPIRVTransforms

    

    ${conversion_libs} ${extension_libs} ${translation_libs}
)

set(COMPILER_HEADERS ${COMP_HEADERS} PARENT_SCOPE)

if(TOOLS)
#    add_subdirectory(vkml-opt)
#    add_subdirectory(vkml-translate)
endif()
