# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 18:05:20 by abelov            #+#    #+#              #
#    Updated: 2024/09/13 18:05:21 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


cmake_minimum_required(VERSION 3.8)

project(philosophers C)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 99)
include_directories(include)
set(FT_LDFLAGS
#        -fsanitize=address
        -fsanitize=undefined
        -fsanitize=thread
        -fno-sanitize-recover
        -fsanitize=float-divide-by-zero
        -fsanitize=float-cast-overflow)
set(FT_CFLAGS
        -Wall -Wextra -Werror
        -Wwrite-strings -Wimplicit
        -Wno-error=unused-parameter
        -Wno-error=unused-function
        -O0
        -masm=att
        -ffunction-sections
        -fdata-sections
        -fomit-frame-pointer
        -fdwarf2-cfi-asm
        -fcf-protection=none
        -mmanual-endbr
        -g3 -gdwarf-3
        -fasynchronous-unwind-tables
#        -fsanitize=address
        -fsanitize=undefined
        -fsanitize=thread
        -fno-sanitize-recover
        -fsanitize=float-divide-by-zero
        -fsanitize=float-cast-overflow)

if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/scratch")
    if(EXISTS "${PROJECT_SOURCE_DIR}/scratch/CMakeLists.txt")
        add_subdirectory(scratch)
    endif()
endif()

file(GLOB_RECURSE TARGET_HEADERS "src/*.h")
list(FILTER TARGET_HEADERS EXCLUDE REGEX "bonus/*" )
file(GLOB_RECURSE TARGET_SOURCES "src/*.c")
list(FILTER TARGET_SOURCES EXCLUDE REGEX "bonus/*")

set(TARGET_NAME "${PROJECT_NAME}_exe")

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(TARGET_LIBRARIES
        ${FT_LIB_NAME}
        Threads::Threads)

add_executable(${TARGET_NAME}
        ${TARGET_HEADERS}
        ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(${TARGET_NAME} "${TARGET_LIBRARIES}")
target_link_options(${TARGET_NAME} PRIVATE "${FT_LDFLAGS}")
target_compile_options(${TARGET_NAME} PRIVATE "${FT_CFLAGS}")
set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "philo")

#==============================================================================#
# Custom targets
#==============================================================================#
add_custom_target(fclean
        COMMAND make -C ${FT_LIB_DIR} fclean)

add_custom_target(re
        COMMAND make -C ${FT_LIB_DIR} re
        COMMAND make -C ${PROJECT_SOURCE_DIR} re)

add_custom_target(norm
        COMMAND make -C ${FT_LIB_DIR} norm
        COMMAND make -C ${PROJECT_SOURCE_DIR} norm)
