cmake_minimum_required(VERSION 3.5.0)
project(JMArkinstallSoA CXX)

add_definitions("-std=c++17")
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


add_executable(example "examples/example.cpp")
target_include_directories(example PUBLIC include)
