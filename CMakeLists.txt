cmake_minimum_required(VERSION 3.20)
project(codewar_kata_c C)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#设置编译、链接参数
set(LINK_FLAGS      -Wl,--gc-sections)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections -Os -Wall")

message(STATUS ${CMAKE_BUILD_TYPE})

#设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 设置静态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 动态库文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin) # 可执行文件目录

# 添加子目录
set(SRCS_DIR ./src/)
aux_source_directory(. SRCS)
add_subdirectory(${SRCS_DIR}/katas)
add_subdirectory(${SRCS_DIR}/basic_algorithm)
add_subdirectory(${SRCS_DIR}/questions)

# 可执行文件
add_executable(main ${SRCS})

# 链接库
target_link_libraries(main m)
target_link_libraries(main hba)
target_link_libraries(main katas)
target_link_libraries(main questions)