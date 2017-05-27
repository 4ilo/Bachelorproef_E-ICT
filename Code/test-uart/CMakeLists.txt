cmake_minimum_required(VERSION 3.2.2)
project(test_uart)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Uart.h Uart.cpp)
add_executable(test_uart ${SOURCE_FILES})