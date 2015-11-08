cmake_minimum_required(VERSION 3.3)
project(stringSearching)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgtest -pthread")

set(SOURCE_FILES main.cpp StringUtils.cpp StringUtils.h)
set(TEST_FILES Tests.cpp StringUtils.cpp StringUtils.h)
add_executable(stringSearching ${SOURCE_FILES})
add_executable(RunTests ${TEST_FILES})
target_link_libraries(RunTests gtest)