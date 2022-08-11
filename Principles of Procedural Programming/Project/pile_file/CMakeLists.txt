cmake_minimum_required(VERSION 3.15)
project(pile_file C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pile_file
        main.c
        pilha.c
        pilha.h)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")