cmake_minimum_required(VERSION 3.24)

project(stf VERSION 0.0.0 DESCRIPTION "A templated math library for graphics" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILD_TESTS TRUE)
endif()

if (BUILD_TESTS)
    include(CTest)
endif()

add_subdirectory(src)
add_subdirectory(deps)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()