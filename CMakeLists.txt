# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

project ("vkml" VERSION 0.1 LANGUAGES C CXX)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(TOOLS "ENABLE TESTING" ON)


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

include(cmake/llvm-project.cmake)

set(LLVM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build/include CACHE PATH "Path to MLIR includes" FORCE)
set(LLVM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/include CACHE PATH "Path to LLVM include" FORCE)
set(LLVM_MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project CACHE PATH "Path to LLVM source" FORCE)
set(LLVM_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build/Release/lib CACHE PATH "Path to LLVM lib" FORCE)

file(GLOB_RECURSE _LIBS CONFIGURE_DEPENDS "${LLVM_LIB_DIR}/*/Release/*.lib" )
set(COMPILER_INCLUDE_DIRS ${LLVM_INCLUDE_DIR} ${LLVM_INCLUDE_DIRS})
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h" "include/*.hpp" )
set(VKML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/compiler/include)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "lib/*.cpp" )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})

add_subdirectory(compiler)
add_library(vkml_lib STATIC ${HEADERS} ${SOURCE})
target_include_directories(vkml_lib PUBLIC ${VKML_INCLUDE_DIRS} ${COMPILER_INCLUDE_DIRS})
add_dependencies(vkml_lib vkml_mlir_compiler_static)
target_link_libraries(vkml_lib PUBLIC vkml_mlir_compiler_static)


add_executable(dev dev/main.cpp)
target_include_directories(dev PRIVATE ${VKML_INCLUDE_DIRS} ${COMPILER_INCLUDE_DIRS})
target_link_libraries(dev PRIVATE vkml_lib)