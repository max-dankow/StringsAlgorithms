cmake_minimum_required(VERSION 3.3)
project(StringUtils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgtest -pthread")

set(SOURCE_FILES Tests/Tests.cpp)
add_executable(Tests ${SOURCE_FILES})
add_executable(Solution main.cpp)

add_library(StringUtils StringUtils.cpp StringUtils.h)
add_subdirectory(SuffixTreeUtils)
add_subdirectory(SuffixArray)

target_link_libraries(Tests gtest StringUtils SuffixTreeUtils SuffixArray)
target_link_libraries(Solution StringUtils SuffixTreeUtils SuffixArray)