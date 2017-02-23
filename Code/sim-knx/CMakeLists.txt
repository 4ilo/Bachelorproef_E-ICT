cmake_minimum_required(VERSION 3.6)
project(sim_knx)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Commando.cpp Commando.h Response.cpp Response.h)
add_executable(sim_knx ${SOURCE_FILES})