cmake_minimum_required(VERSION 3.0)
project(Vector LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_FILES       test/main.c
                    src/Vector.c
)

include_directories(include)

add_executable(Vector
    ${LIB_FILES}
)