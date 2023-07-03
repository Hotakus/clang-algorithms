cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
project(hotakus-clang-algorithms
        LANGUAGES C
        VERSION 1.1.0.0
        DESCRIPTION "Hotakus' clang algorithms (hca)"
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

# 设置工具链
if (CW_KATA_ARM)
    set(ARM_CPU         cortex-m3)
    set(ARM_ARCH        armv7)
    set(ARM_FLOAT_ABI   soft) # soft softfp hard
    set(ARM_FPU         "") # "-mfpu=neon-vfpv4"
    set(TOOL_C_PATH     "/home/hotakus/dl/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
    SET(CMAKE_C_COMPILER ${TOOL_C_PATH})
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -march=${ARM_ARCH} -mfloat-abi=${ARM_FLOAT_ABI} ${ARM_FPU}")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} --specs=nosys.specs -mno-unaligned-access -fno-aggressive-loop-optimizations")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif ()

#设置编译、链接参数等
set(LINK_FLAGS      "${LINK_FLAGS} -Wl,-Map=object.map,--cref,--gc-section")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections -Wall")
message(WARNING     "${LINK_FLAGS}")
message(WARNING     "${CMAKE_C_FLAGS}")

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
set(KATAS_SRC ${SRCS_DIR}/katas)
set(DS_SRC ${SRCS_DIR}/data_structures)
set(ALGORITHM_SRC ${SRCS_DIR}/algorithms)
set(QUESTION_SRC ${SRCS_DIR}/questions)

aux_source_directory(. ROOT_SRCS)
add_subdirectory(${KATAS_SRC})
add_subdirectory(${DS_SRC})
add_subdirectory(${ALGORITHM_SRC})
add_subdirectory(${QUESTION_SRC})

# lib postfix
#set(CMAKE_DEBUG_POSTFIX "_debug")
#set(CMAKE_RELEASE_POSTFIX "_release")

# 可执行文件
#set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_debug")
#set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
if (HCA_TEST)
    add_executable(hca ${ROOT_SRCS})
else ()
    add_library(hca STATIC ${ROOT_SRCS})
endif ()


# 链接库
target_link_libraries(hca hba)
target_link_libraries(hca katas)
target_link_libraries(hca questions)
target_link_libraries(hca datastructures)

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


