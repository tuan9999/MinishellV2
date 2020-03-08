cmake_minimum_required(VERSION 3.15)
project(memeshell420 C)

set(CMAKE_C_STANDARD 90)

file(GLOB srcs
        "src/*.c"
        "src/runtime_loop/*.c"
        "src/std/*.c"
        "src/parser/*.c"
        "src/*/*.c"
        )

add_executable(minishell ${srcs})
include_directories(include libft libftprintf/include)
