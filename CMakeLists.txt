cmake_minimum_required(VERSION 2.8.10)

# for 3.x+
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

# Project names
set(PROJECT_NAME bitkeg)
project(${PROJECT_NAME} VERSION 0.1)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_library(bitkeg ${SRC_FILES})

#gtest
add_subdirectory(./lib/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/gtest/*.cc)

add_executable(runUnitTests ${TEST_SRC_FILES})

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests bitkeg)

add_test(UnitTests runUnitTests)