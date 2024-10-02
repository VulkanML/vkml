project (vkrt)

include_directories(${kompute_SOURCE_DIR}/src/include)


add_library(vkrt INTERFACE ${CMAKE_INCLUDE_CURRENT_DIR}/rt.h ${CMAKE_INCLUDE_CURRENT_DIR}/vkrt.cpp)

target_link_libraries(vkrt PUBLIC kompute::kompute)

