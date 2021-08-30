cmake_minimum_required(VERSION 3.17)
project(3_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(3_1 main.c)
target_link_libraries(3_1 PRIVATE m)