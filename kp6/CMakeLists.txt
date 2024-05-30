cmake_minimum_required(VERSION 3.26)
project(C C)

set(CMAKE_C_STANDARD 99)

add_executable(. main.c
        lab.c)
add_executable(proc processing.c
        lab.c)