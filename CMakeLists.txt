cmake_minimum_required(VERSION 3.25)
project(codewar_kata_c C)

set(CMAKE_C_STANDARD 23)

add_executable(codewar_kata_c
        main.c
        main.h
        katas/sum_of_positive.c
        katas/sum_of_positive.h
        katas/find_odd_int.h
        katas/find_odd_int.c
        base_algorithm/dict.c
        base_algorithm/dict.h
        base_algorithm/chain.c
        base_algorithm/chain.h
        base_algorithm/utilities.c
        base_algorithm/utilities.h)
