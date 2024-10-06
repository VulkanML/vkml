project (vkrt)

add_library(vkrt STATIC include/rt.h vkrt.cpp)
target_include_directories(vkrt INTERFACE ${kompute_SOURCE_DIR}/src/include)
target_include_directories(vkrt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(vkrt "kompute")

