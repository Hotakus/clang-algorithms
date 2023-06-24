cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
project(codewar_kata_c
        LANGUAGES C
        VERSION 1.0.0.0
        DESCRIPTION "Practices"
        HOMEPAGE_URL https://www.codewars.com/users/Hotakus
        )

# 指定版本号的配置文件
configure_file(${PROJECT_SOURCE_DIR}/version.h.in ${PROJECT_SOURCE_DIR}/version.h)

# 系统设置
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Current platform: Linux ")
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "Current platform: Windows")
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "Current platform: FreeBSD")
else ()
    MESSAGE(STATUS "Unknown platform: ${CMAKE_SYSTEM_NAME}")
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")
MESSAGE(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")

#设置编译、链接参数等
set(LINK_FLAGS      -Wl,--gc-sections)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections -Os -Wall -s")
message(WARNING "${CMAKE_C_FLAGS}")

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Set up ccache ...")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else ()
    message(WARNING "Can not find ccache. (you can ignore this tip.)")
endif()

#设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 设置静态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 动态库文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin) # 可执行文件目录

# 添加子目录
set(SRCS_DIR ${PROJECT_SOURCE_DIR}/src/)
aux_source_directory(. ROOT_SRCS)
add_subdirectory(${SRCS_DIR}/katas)
add_subdirectory(${SRCS_DIR}/basic_algorithm)
add_subdirectory(${SRCS_DIR}/questions)

# lib postfix
set(CMAKE_DEBUG_POSTFIX "_debug")
#set(CMAKE_RELEASE_POSTFIX "_release")

# 可执行文件
#set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_debug")
# set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
add_executable(main ${ROOT_SRCS})

# 链接库
target_link_libraries(main m)
target_link_libraries(main hba)
target_link_libraries(main katas)
target_link_libraries(main questions)

# 测试信息
#message("PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
#message("PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
#
#message("PROJECT_NAME ${PROJECT_NAME}")
#message("PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION}")
#message("PROJECT_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}")
#
#message("PROJECT_VERSION ${PROJECT_VERSION}")
#message("PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}")
#message("PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR}")
#message("PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH}")
#message("PROJECT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK}")


