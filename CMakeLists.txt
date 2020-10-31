cmake_minimum_required(VERSION 3.18)

project(bitkeg VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(bitkeg SHARED src/bitkeg.cc)