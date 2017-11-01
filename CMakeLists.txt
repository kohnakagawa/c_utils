cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99")
add_definitions(-D_POSIX_C_SOURCE=200112L)

file(GLOB eclib_c_src *.c)
set(eclib_srcs ${eclib_c_src})

# add_library(eclib SHARED ${eclib_srcs})
add_library(eclib STATIC ${eclib_srcs})
