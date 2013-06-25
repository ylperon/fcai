cmake_minimum_required(VERSION 2.8)

project(test_all)

set(SOURCE test_all.cpp)

include_directories(../include)

add_executable(test_all ${SOURCE})
