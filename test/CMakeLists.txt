cmake_minimum_required(VERSION 3.20)
project(krt_tests)

add_executable(krt_tests 
    rt_test.cpp
)

target_link_libraries(krt_tests PRIVATE krt)

add_test(NAME krt_tests COMMAND krt_tests)
set_property(TARGET krt_tests PROPERTY FOLDER "tests")
