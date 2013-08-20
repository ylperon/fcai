cmake_minimum_required(VERSION 2.8)

project(fcai)

OPTION(DEBUG_MODE "Enable debug output [default: OFF]" ON)

SET(CMAKE_CXX_WARN_FLAGS " -Wall -pedantic -Werror")

IF(DEBUG_MODE MATCHES "ON")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
ENDIF(DEBUG_MODE MATCHES "ON")

IF(DEBUG_MODE MATCHES "ON")
    MESSAGE(STATUS "#### ATTENTION #################################################")
    MESSAGE(STATUS "#### Debug mode enabled. Use this option only for testing!  ####")
    MESSAGE(STATUS "#### ATTENTION #################################################")
ENDIF(DEBUG_MODE MATCHES "ON")

include_directories(src)

set(FCAI_SRC src/fca_implication.cpp
             src/fca_concept.cpp
             src/fca_context.cpp
             src/fca_context_string.cpp)
set(TEST_SRC tests/test_util.cpp
             tests/test_bitset.cpp
             tests/test_implication.cpp
             tests/test_concept.cpp
             tests/test_context.cpp
             tests/test_context_string.cpp)

add_library(fcai ${FCAI_SRC})
add_library(test ${TEST_SRC})

add_executable(test_all tests/test_all.cpp)

target_link_libraries(test_all fcai
                               test)
