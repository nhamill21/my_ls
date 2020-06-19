cmake_minimum_required(VERSION 3.10)
project(my_ls C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)
set(SRCS src/main.c src/parse.c src/stack.c src/heap.c src/list.c src/exit.c src/test.c)
add_executable(my_ls ${SRCS})