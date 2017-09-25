cmake_minimum_required(VERSION 2.8)
# set(CMAKE_VERBOSE_MAKEFILE 1)

include_directories(../)

set(CMAKE_INCLUDE_PATH )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage --coverage")

set(GCOV_LINK_LIBS gcov)
set(CUNIT_LINK_LIBS cunit)
set(LINK_LIBS ${GCOV_LINK_LIBS} ${CUNIT_LINK_LIBS})

add_executable(vector_test vector_test.c ../utils.c ../err_msgs.c)
target_link_libraries(vector_test ${LINK_LIBS})

add_executable(stack_test stack_test.c ../utils.c ../err_msgs.c)
target_link_libraries(stack_test ${LINK_LIBS})

add_executable(string_c_test string_c_test.c ../string_c.c ../utils.c ../err_msgs.c)
target_link_libraries(string_c_test ${LINK_LIBS})

add_definitions(-D_POSIX_C_SOURCE=200112L)
add_executable(fsystem_test filesystem_test.c ../filesystem.c ../string_c.c ../utils.c ../err_msgs.c)
target_link_libraries(fsystem_test ${LINK_LIBS})

add_executable(vector3_test vector3_test.c)
target_link_libraries(vector3_test ${LINK_LIBS} m)

add_executable(algorithm_test algorithm_test.c)
target_link_libraries(algorithm_test ${LINK_LIBS})
