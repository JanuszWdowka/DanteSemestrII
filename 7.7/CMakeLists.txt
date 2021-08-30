cmake_minimum_required(VERSION 3.17)
project(7_7 C)

set(CMAKE_C_STANDARD 99)

add_executable(7_7 main.c)

target_link_libraries(7_7 PRIVATE m)