cmake_minimum_required(VERSION 3.0)
project(minibash LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_FILES main.c Vector/src/Vector.c src/Executable.c src/Process.c)

# add_subdirectory()

include_directories("include" "Vector/include")

add_executable(minibash ${LIB_FILES})
