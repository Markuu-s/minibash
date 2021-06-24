cmake_minimum_required(VERSION 3.0)
project(minibash LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_FILES       main.c
                    src/Executable.c
                    src/Process.c
)

include_directories(lib)

add_executable(minibash
    ${LIB_FILES}
)