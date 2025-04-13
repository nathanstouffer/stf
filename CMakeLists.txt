cmake_minimum_required(VERSION 3.24)

project(stf VERSION 0.0.0 DESCRIPTION "A templated math library for graphics" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# set property so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(STF_SUPPRESS_ANONYMOUS_STRUCT_WARNINGS "Suppress warnings related to anonymous structs" TRUE)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILD_TESTS TRUE)
    enable_testing()
    option(STF_TESTS_WARNINGS_AS_ERROR "Enable warnings as errors in tests" FALSE)

    set(BUILD_DOCS TRUE)
endif()

add_subdirectory(code)