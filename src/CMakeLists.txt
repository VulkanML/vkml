# CMakeList.txt : CMake project for vkml, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (vkml "vkml.cpp" "vkml.h")

set(LLVM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../llvm/_install/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)
set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../mlir/_install/lib/cmake/mlir)
find_package(MLIR REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

target_link_libraries(vkml ${llvm_libs})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET vkml PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
