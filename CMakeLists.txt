cmake_minimum_required(VERSION 3.23)
project(glfw_proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(program main.cpp glad.c)

include_directories(include)
link_directories(lib-arm64)

find_package(glfw3)
target_link_libraries(program glfw)

find_library(IOKIT_FRAMEWORK IOKit)
find_library(COCOA_FRAMEWORK Cocoa)

target_link_libraries(program ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK})
