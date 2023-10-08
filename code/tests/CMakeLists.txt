cmake_minimum_required(VERSION 3.24)

project(stf-tests VERSION 1.0.0)

add_executable(tests tests.cpp)

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src/)