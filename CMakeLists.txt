cmake_minimum_required(VERSION 3.10)
project(my_ls C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)
set(SRCS src/main.c src/init.c src/flag_d.c src/utils_str.c src/trash.c src/utils.c src/recursive.c src/non_recursive.c src/print.c src/flag_d.c src/stack.c src/heap.c src/list.c src/exit.c src/test.c)
add_executable(my_ls ${SRCS})