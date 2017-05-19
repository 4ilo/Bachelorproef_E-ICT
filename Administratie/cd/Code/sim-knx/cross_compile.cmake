INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

SET(GPP_COMPILER_FLAGS "-std=c++11")
add_definitions(${GPP_COMPILER_FLAGS})

# specify the cross compiler
CMAKE_FORCE_C_COMPILER(/home/olivier/Documents/School/Bachelorproef/custom-linux/buildroot-2016.11.2/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(/home/olivier/Documents/School/Bachelorproef/custom-linux/buildroot-2016.11.2/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-g++ GNU)
