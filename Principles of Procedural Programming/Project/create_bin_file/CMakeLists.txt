cmake_minimum_required(VERSION 3.15)
project(create_bin_file C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(create_bin_file
        get_one_line.c
        get_one_line.h
        main.c)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")