cmake_minimum_required(VERSION 3.12)

project(vkml-mlir LANGUAGES CXX C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
unset(LLVM_DIR CACHE)
unset(MLIR_DIR CACHE)

add_subdirectory(ext/kompute _deps EXCLUDE_FROM_ALL )

set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../llvm-project/build/lib/cmake/mlir)
set(LLVM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../llvm-project/build/lib/cmake/llvm)
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

find_package(MLIR REQUIRED CONFIG)
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(LIT_ARGS_DEFAULT "-sv")
if (MSVC_IDE OR XCODE)
    set(LIT_ARGS_DEFAULT "${LIT_ARGS_DEFAULT} --no-progress-bar")
endif()
set(LLVM_LIT_ARGS "${LIT_ARGS_DEFAULT}" CACHE STRING "Default options for lit")

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(TableGen)
include(AddLLVM)
include(AddMLIR)
set(BACKEND_PACKAGE_STRING "LLVM ${LLVM_PACKAGE_VERSION}")

set(VKML_MLIR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(VKML_MLIR_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Building VKML-mlir project at ${VKML_MLIR_SOURCE_DIR} (into ${VKML_MLIR_BINARY_DIR})")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

function(vkml_mlir_target_includes target)
  set(_dirs
    $<BUILD_INTERFACE:${MLIR_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${VKML_MLIR_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${VKML_MLIR_BINARY_DIR}/include>
  )
  
  target_include_directories(${target} PUBLIC ${_dirs})
  if(TARGET obj.${target})
    target_include_directories(obj.${target} PRIVATE ${_dirs})
  endif()
endfunction()



list(APPEND CMAKE_MODULE_PATH ${MLIR_MAIN_SRC_DIR}/cmake/modules)
list(APPEND CMAKE_MODULE_PATH ${LLVM_MAIN_SRC_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build_tools/cmake)

include(TableGen)
include(AddLLVM)
include(AddMLIR)

option(KOMPUTE_OPT_FROM_SOURCE "Whether to build example from source or from git fetch repo" ON)
set(MLIR_DEPS_LIBS
  MLIRIR
  MLIRPass
  MLIRTransforms
  MLIRGPUDialect
  SPIRV
)
  



add_subdirectory(include)
add_subdirectory(lib)

add_subdirectory(test)


