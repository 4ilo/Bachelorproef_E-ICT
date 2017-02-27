cmake_minimum_required(VERSION 3.3)

#set(REPO /home/olivier/Documents/School/Bachelorproef/Code/testgtest/.repo)

project(Test)

project(Example)

include(CTest)
enable_testing()

include(lib/DownloadProject.cmake)
download_project(
        PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

#set(test_SRCS ../src/main.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock core)
#add_test(runUnitTests runUnutTests)