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

include(cmake/llvm-project.cmake)
list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/ext/llvm-project/build/lib/cmake/mlir)
list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/ext/llvm-project/build/lib/cmake/llvm)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h" "include/*.hpp" )
set(VKML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/compiler/include)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "lib/*.cpp" )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})

add_subdirectory(compiler)
add_library(vkml_lib STATIC ${HEADERS} ${SOURCE})
target_include_directories(vkml_lib PUBLIC ${VKML_INCLUDE_DIRS} )
add_dependencies(vkml_lib vkml_mlir_compiler)
target_link_libraries(vkml_lib PUBLIC vkml_mlir_compiler)


add_executable(dev dev/main.cpp)
target_include_directories(dev PRIVATE ${VKML_INCLUDE_DIRS})
target_link_libraries(dev PRIVATE vkml_lib)