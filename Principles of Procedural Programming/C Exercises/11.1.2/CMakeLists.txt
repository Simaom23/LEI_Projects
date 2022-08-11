cmake_minimum_required(VERSION 3.15)
project(11_1_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(11_1_2 main.c)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")
