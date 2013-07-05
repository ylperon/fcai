cmake_minimum_required(VERSION 2.8)

project(test_all)

set(SOURCE_EXE test_all.cpp
               test_util.cpp
               test_bitset.cpp
               test_implication.cpp)

include_directories(../include)

add_executable(test_all ${SOURCE_EXE})
