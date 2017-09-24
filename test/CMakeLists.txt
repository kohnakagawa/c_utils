cmake_minimum_required(VERSION 2.8)
# set(CMAKE_VERBOSE_MAKEFILE 1)

include_directories(../)

set(CMAKE_INCLUDE_PATH )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c99")

add_executable(vector_test vector_test.c ../utils.c ../err_msgs.c)
target_link_libraries(vector_test cunit)

add_executable(stack_test stack_test.c ../utils.c ../err_msgs.c)
target_link_libraries(stack_test cunit)

add_executable(string_c_test string_c_test.c ../string_c.c ../utils.c ../err_msgs.c)
target_link_libraries(string_c_test cunit)

add_executable(file_test filesystem_test.c ../filesystem.c ../string_c.c ../utils.c ../err_msgs.c)

add_executable(vector3_test vector3_test.c)
target_link_libraries(vector3_test cunit m)