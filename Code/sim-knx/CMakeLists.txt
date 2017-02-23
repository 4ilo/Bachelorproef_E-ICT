cmake_minimum_required(VERSION 3.6)
project(sim_knx)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Commando.cpp inc/Commando.h src/Response.cpp inc/Response.h src/Object.cpp inc/Object.h inc/commands.h)
add_executable(sim_knx ${SOURCE_FILES})