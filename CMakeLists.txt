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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(${TARGET_NAME} LANGUAGES CXX C)

add_subdirectory(compiler)
add_subdirectory(runtime)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "inc/*.h" "inc/*.hpp" )
set(VKML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "lib/*.cpp" )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE})


add_library(vkml-lib STATIC ${HEADERS} ${SOURCE})

target_link_libraries(vkml-lib PUBLIC vkml-rt)
target_link_libraries(vkml-lib PUBLIC vkml-compiler)
target_include_directories(vkml-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(vkml-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compiler/inc)
target_include_directories(vkml-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/runtime/src/inc)
target_include_directories(vkml-lib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/compiler/tablegen )
get_property(vkml_compiler_headers GLOBAL PROPERTY VKML_COMPILER_HEADERS)
get_property(vkrt_headers GLOBAL PROPERTY VKRT_HEADERS)
target_include_directories(vkml-lib PUBLIC ${vkrt_headers})
target_include_directories(vkml-lib PUBLIC ${vkml_compiler_headers})


set_property(GLOBAL PROPERTY VKML_HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/compiler/inc ${CMAKE_CURRENT_SOURCE_DIR}/runtime/inc
${CMAKE_CURRENT_BINARY_DIR}/compiler/tablegen ${vkml_compiler_headers} ${vkrt_headers})

get_property(vkml-headers GLOBAL PROPERTY VKML_HEADERS)


add_executable(dev dev/main.cpp)
target_include_directories(dev PRIVATE ${vkml_headers})
target_link_libraries(dev PRIVATE vkml-lib)


