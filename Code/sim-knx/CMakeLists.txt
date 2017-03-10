cmake_minimum_required(VERSION 3.2)
project(sim-knx)

add_definitions( -DUART_DEBUG=1 )

add_subdirectory(sim-knx)
add_subdirectory(test)