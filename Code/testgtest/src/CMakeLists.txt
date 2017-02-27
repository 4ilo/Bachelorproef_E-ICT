set(core_SRCS main.cpp file.cpp file.h)

add_library(core ${core_SRCS})
add_executable(testgtest main.cpp)
target_link_libraries(testgtest core)