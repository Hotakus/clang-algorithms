cmake_minimum_required(VERSION 3.21)
project(codewar_kata_c C)

set(CMAKE_C_STANDARD 23)

add_subdirectory(base_algorithm)
aux_source_directory(. SRCS)

add_executable(kata ${SRCS})

target_link_libraries(kata m)
target_link_libraries(kata hba)