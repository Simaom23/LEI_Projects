cmake_minimum_required(VERSION 3.15)
project(Ex10_1_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ex10_1_1
        main.c)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")
