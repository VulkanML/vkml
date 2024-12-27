# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

project ("vkml")
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(TOOLS "ENABLE TESTING" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MLIR_VERSION 19.1.6)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
	file( DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-${MLIR_VERSION}/cmake-${MLIR_VERSION}.src.tar.xz"  ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz
		STATUS DOWNLOAD_STATUS )
		
	message(STATUS " cmake Download status: ${DOWNLOAD_STATUS}")
	file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.src/Modules DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
	file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.src)
	file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz)
	message(STATUS " cmake Extraction done")
endif()


include(cmake/mlir.cmake)

set(LLVM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/llvm/_install/lib/cmake/llvm )
set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_install/lib/cmake/mlir )
set(CMAKE_PREFIX_PATH ${LLVM_DIR}; ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH ${MLIR_DIR}; ${CMAKE_PREFIX_PATH})

find_package(MLIR REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include(TableGen)
include(AddLLVM)
include(HandleLLVMOptions)
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

include(AddMLIR)

# Include sub-projects.
add_subdirectory("src")
if(NOT TOOLS)
	add_subdirectory("tools")
endif()