cmake_minimum_required(VERSION 3.17)
project(4_11 C)

set(CMAKE_C_STANDARD 99)

add_executable(4_11 main.c)
target_link_libraries(4_11 PRIVATE m)