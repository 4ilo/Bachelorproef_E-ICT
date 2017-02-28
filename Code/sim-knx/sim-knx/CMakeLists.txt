cmake_minimum_required(VERSION 2.8)
project(sim_knx)

set(CMAKE_CXX_STANDARD 11)

SET(GPP_COMPILER_FLAGS "-std=c++11")
add_definitions(${GPP_COMPILER_FLAGS})

set(SOURCE_FILES main.cpp src/Commando.cpp inc/Commando.h src/Response.cpp inc/Response.h src/Object.cpp inc/Object.h inc/commands.h src/Uart.cpp inc/Uart.h src/Device.cpp inc/Device.h)
add_executable(sim_knx ${SOURCE_FILES})
add_library(sim_knx_source ${SOURCE_FILES})