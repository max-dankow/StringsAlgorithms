cmake_minimum_required(VERSION 3.3)
project(StringUtils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgtest -pthread")

set(SOURCE_FILES Tests/Tests.cpp)
add_executable(Tests ${SOURCE_FILES})

add_library(StringUtils StringUtils.cpp StringUtils.h)
add_subdirectory(SuffixTreeUtils)

target_link_libraries(Tests gtest StringUtils)