
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

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "*.cpp" "*.h" "*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})
add_library(${STATIC_TARGET_NAME} STATIC ${SOURCE})

set(COMPILER_LIBS     
    ${LLVM_LIB_DIR}/MLIRBytecodeWriter.lib
    ${LLVM_LIB_DIR}/MLIRAsmParser.lib
    ${LLVM_LIB_DIR}/MLIRBytecodeReader.lib
    ${LLVM_LIB_DIR}/MLIRObservers.lib
    ${LLVM_LIB_DIR}/MLIRAnalysis.lib
    ${LLVM_LIB_DIR}/MLIRPass.lib
    ${LLVM_LIB_DIR}/MLIRParser.lib
    ${LLVM_LIB_DIR}/MLIRPluginsLib.lib
    ${LLVM_LIB_DIR}/MLIRTransforms.lib
    ${LLVM_LIB_DIR}/MLIRTransformUtils.lib
    ${LLVM_LIB_DIR}/MLIRSupport.lib
    ${LLVM_LIB_DIR}/MLIRDialect.lib
    ${LLVM_LIB_DIR}/MLIRDialectUtils.lib
    ${LLVM_LIB_DIR}/MLIRRewrite.lib
    ${LLVM_LIB_DIR}/MLIRRewritePDL.lib

    ${LLVM_LIB_DIR}/MLIRInferIntRangeCommon.lib
    ${LLVM_LIB_DIR}/MLIRInferIntRangeInterface.lib
    ${LLVM_LIB_DIR}/MLIRInferTypeOpInterface.lib

    ${LLVM_LIB_DIR}/MLIRBytecodeOpInterface.lib
    ${LLVM_LIB_DIR}/MLIRCastInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRControlFlowInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRInferTypeOpInterface.lib
    ${LLVM_LIB_DIR}/MLIRMemorySlotInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRShapedOpInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRSideEffectInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRValueBoundsOpInterface.lib
    ${LLVM_LIB_DIR}/MLIRViewLikeInterface.lib
    ${LLVM_LIB_DIR}/MLIRLoopLikeInterface.lib
    ${LLVM_LIB_DIR}/MLIRValueBoundsOpInterface.lib
    ${LLVM_LIB_DIR}/MLIRFunctionInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRDataLayoutInterfaces.lib
    ${LLVM_LIB_DIR}/MLIRRuntimeVerifiableOpInterface.lib

    ${LLVM_LIB_DIR}/MLIRPDLDialect.lib
    ${LLVM_LIB_DIR}/MLIRPDLInterpDialect.lib
    ${LLVM_LIB_DIR}/MLIRPDLToPDLInterp.lib

    ${LLVM_LIB_DIR}/MLIRDLTIDialect.lib
    ${LLVM_LIB_DIR}/MLIRUBDialect.lib
    ${LLVM_LIB_DIR}/MLIRComplexDialect.lib
    ${LLVM_LIB_DIR}/MLIRArithDialect.lib
    ${LLVM_LIB_DIR}/MLIRArithUtils.lib
    ${LLVM_LIB_DIR}/MLIRMemRefDialect.lib

    #${LLVM_LIB_DIR}/MLIRSCFDialect.lib
    #${LLVM_LIB_DIR}/MLIRFuncDialect.lib

    ${LLVM_LIB_DIR}/MLIRGPUDialect.lib
    ${LLVM_LIB_DIR}/MLIRSPIRVDialect.lib
    ${LLVM_LIB_DIR}/MLIRSPIRVBinaryUtils.lib
    ${LLVM_LIB_DIR}/MLIRSPIRVSerialization.lib
    ${LLVM_LIB_DIR}/MLIRIR.lib

    ${LLVM_LIB_DIR}/MLIRGPUTransforms.lib

    ${LLVM_LIB_DIR}/MLIRSPIRVTransforms.lib
    ${LLVM_LIB_DIR}/MLIRSPIRVTarget.lib

    #${LLVM_LIB_DIR}/MLIRArithToSPIRV.lib
    #${LLVM_LIB_DIR}/MLIRFuncToSPIRV.lib
    #${LLVM_LIB_DIR}/MLIRGPUToSPIRV.lib
    #${LLVM_LIB_DIR}/MLIRMemRefToSPIRV.lib
    #${LLVM_LIB_DIR}/MLIRGPUToVulkanTransforms.lib
     
    ${LLVM_LIB_DIR}/LLVMSupport.lib
    ntdll.lib
)

include_directories(${COMPILER_INCLUDE_DIRS})

target_link_libraries(${STATIC_TARGET_NAME} PUBLIC ${COMPILER_LIBS})
if(TOOLS)
    add_subdirectory(vkml-opt)
    add_subdirectory(vkml-translate)
endif()
