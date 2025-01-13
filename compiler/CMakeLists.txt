
set(TARGET_NAME vkml_mlir_compiler)
set(TBLEGEN_TARGET_NAME "${TARGET_NAME}_tblgen")
set(STATIC_TARGET_NAME "${TARGET_NAME}_static")


execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-decls --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlDialect.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include --write-if-changed --gen-dialect-defs --dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlDialect.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlBase.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlTypes.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-typedef-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlTypes.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlTypes.td)

execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-decls -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/include/vkmlOps.h.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)
execute_process(COMMAND ${TABLEGEN_EXE} -I ${MLIR_MAIN_SRC_DIR}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/tablegen --write-if-changed -gen-op-defs -dialect=vkml -o ${CMAKE_CURRENT_SOURCE_DIR}/src/vkmlOps.cpp.inc ${CMAKE_CURRENT_SOURCE_DIR}/tablegen/Dialect/vkmlOps.td)

project(${TARGET_NAME} LANGUAGES CXX C)


file(GLOB_RECURSE COMP_SOURCES CONFIGURE_DEPENDS "*.cpp" )
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h" "*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${COMP_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})

find_package(MLIR CONFIG REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include(TableGen)
include(AddLLVM)
include(AddMLIR)

get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)
get_property(translation_libs GLOBAL PROPERTY MLIR_TRANSLATION_LIBS)

add_definitions(${MLIR_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${HEADERS})

add_mlir_aggregate(${TARGET_NAME}
    STATIC
    ${COMP_SOURCES}   ${HEADERS}

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

    ${conversion_libs}
    ${extension_libs}
    ${translation_libs} 
)


if(TOOLS)
    add_subdirectory(vkml-opt)
    add_subdirectory(vkml-translate)
endif()
