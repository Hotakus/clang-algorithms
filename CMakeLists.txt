cmake_minimum_required(VERSION 3.21)
project(codewar_kata_c C)

set(CMAKE_C_STANDARD 23)

aux_source_directory(. SRCS)
add_subdirectory(katas)
add_subdirectory(base_algorithm)


add_executable(main ${SRCS})

target_link_libraries(main m)
target_link_libraries(main hba)
target_link_libraries(main katas)