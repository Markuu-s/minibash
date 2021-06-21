cmake_minimum_required(VERSION 3.13)
project(minibash C)

set(CMAKE_C_STANDARD 99)

add_executable(minibash main.c src/*.c)