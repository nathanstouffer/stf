cmake_minimum_required(VERSION 3.24)

project(stf VERSION 0.0.0 DESCRIPTION "A templated math library for graphics" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# set up the coverage config
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI)
if (IS_MULTI_CONFIG)
    if (NOT "Coverage" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Coverage)
    endif()
else()
    set(KNOWN_BUILD_TYPES Debug Release RelWithDebInfo Coverage)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${KNOWN_BUILD_TYPES})
    if (NOT CMAKE_BUILD_TYPE IN_LIST KNOWN_BUILD_TYPES)
        message(FATAL_ERROR "Unkown build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

mark_as_advanced(
    CMAKE_C_FLAGS_COVERAGE
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    CMAKE_STATIC_LINKER_FLAGS_COVERAGE
    CMAKE_MODULE_LINKER_FLAGS_COVERAGE
)

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