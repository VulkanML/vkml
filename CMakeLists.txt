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

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/out/cmake/Modules)
	file( DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-${MLIR_VERSION}/cmake-${MLIR_VERSION}.src.tar.xz"  ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz
		STATUS DOWNLOAD_STATUS )		
	message(STATUS " cmake Download status: ${DOWNLOAD_STATUS}")

	file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
	file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.tar.xz)
	message(STATUS " cmake Extraction done")

	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.src/Modules DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out//cmake)
	file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/cmake-${MLIR_VERSION}.src)
	message(STATUS " cmake file processing done")
endif()


include(cmake/mlir.cmake)

set(LLVM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm/_build/lib/cmake/llvm CACHE PATH "Path to LLVM CMake files" FORCE)
set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build/lib/cmake/mlir CACHE PATH "Path to MLIR CMake files" FORCE)
set(TABLEGEN_EXE ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build/bin/Debug/mlir-tblgen.exe CACHE FILEPATH "Path to mlir-tblgen" FORCE)

set(LLVM_MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm CACHE PATH "Path to LLVM source" FORCE)
set(LLVM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm/include CACHE PATH "Path to LLVM include" FORCE)
set(LLVM_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm/_build/lib CACHE PATH "Path to LLVM lib" FORCE)
set(MLIR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/include CACHE PATH "Path to MLIR include" FORCE)
set(MLIR_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build/lib CACHE PATH "Path to MLIR lib" FORCE)
set(MLIR_MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir CACHE PATH "Path to MLIR source" FORCE)


add_subdirectory(compiler)
add_subdirectory(include)
add_subdirectory(lib)


if(NOT LLVM_INSTALL_TOOLCHAIN_ONLY)
	install(DIRECTORY include/vkml-mlir 
			DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
			COMPONENT vkml-mlir-headers
			FILES_MATCHING
			PATTERN "*.def"
			PATTERN "*.h"
			PATTERN "*.inc"
			PATTERN "*.td"
			PATTERN "LICENSE.TXT"
	)
	install(DIRECTORY ${VKML_MLIR_BINARY_DIR}/include/vkml-mlir
			DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
			COMPONENT vkml-mlir-headers
			FILES_MATCHING
			PATTERN "*.def"
			PATTERN "*.h"
			PATTERN "*.gen"
			PATTERN "*.inc"
			PATTERN "*.td"
			PATTERN "CMakeFiles" EXCLUDE
			PATTERN "config.h" EXCLUDE
	)

	if(NOT LLVM_ENABLE_IDE)
		add_llvm_install_targets(install-vkml-mlir-headers
				DEPENDS vkml-mlir-headers
				COMPONENT vkml-mlir-headers
		)
	endif()
endif()
