cmake_minimum_required(VERSION 3.3)
project(stringSearching)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgtest -pthread")

set(SOURCE_FILES main.cpp StringUtils.cpp StringUtils.h SuffixTreeUtils/ISuffixTreeBuilder.h SuffixTreeUtils/SuffixTree.cpp SuffixTreeUtils/SuffixTree.h SuffixTreeUtils/UkkonenAlgorithm.cpp SuffixTreeUtils/UkkonenAlgorithm.h SuffixTreeUtils/SuffixTreeNode.cpp SuffixTreeUtils/SuffixTreeNode.h)
#set(TEST_FILES Tests/Tests.cpp StringUtils.cpp StringUtils.h SuffixTreeUtils/ISuffixTreeBuilder.h SuffixTreeUtils/UkkonenAlgorithm.cpp SuffixTreeUtils/UkkonenAlgorithm.h SuffixTreeUtils/SuffixTreeNode.cpp SuffixTreeUtils/SuffixTreeNode.h)
add_executable(stringSearching ${SOURCE_FILES})
add_executable(RunTests ${SOURCE_FILES} Tests)
target_link_libraries(RunTests gtest)