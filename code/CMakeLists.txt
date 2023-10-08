cmake_minimum_required(VERSION 3.24)

project(stf VERSION 1.0.0 DESCRIPTION "A templated math library for graphics" LANGUAGES CXX)

include(CTest)

add_subdirectory(deps)
add_subdirectory(tests)