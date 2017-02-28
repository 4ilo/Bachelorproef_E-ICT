cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(Test)
project(Example)

include(CTest)
enable_testing()

add_subdirectory(lib/googletest)

set(test_SRCS ../sim-knx/inc/Commando.h Commando_tests.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock sim_knx_source)
#add_test(runUnitTests runUnutTests)