cmake_minimum_required(VERSION 2.8)

project(fcai)

include_directories(src)

set(FCAI_SRC src/fca_implication.cpp
             src/fca_concept.cpp
             src/fca_context.cpp)
set(TEST_SRC tests/test_util.cpp
             tests/test_bitset.cpp
             tests/test_implication.cpp
             tests/test_concept.cpp
             tests/test_context.cpp)

add_library(fcai ${FCAI_SRC})
add_library(test ${TEST_SRC})

add_executable(test_all tests/test_all.cpp)

target_link_libraries(test_all fcai
                               test)
