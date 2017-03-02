cmake_minimum_required(VERSION 3.6)
project(testJson)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp json.hpp)
add_executable(testJson ${SOURCE_FILES})