
add_executable(vkml-translate main.cpp)
add_dependencies(vkml-translate vkml_mlir_compiler_static)
target_include_directories(vkml-translate PRIVATE ../include)
target_include_directories(vkml-translate PRIVATE ${COMPILER_INCLUDE_DIRS})
target_link_libraries(vkml-translate PRIVATE vkml_mlir_compiler_static )