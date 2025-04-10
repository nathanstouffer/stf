cmake_minimum_required(VERSION 3.24)

project(stf VERSION 0.0.0 DESCRIPTION "A templated math library for graphics" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# set property so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILD_TESTS TRUE)
    enable_testing()
    set(BUILD_DOCS TRUE)
    message(INFO "System Name: ${CMAKE_SYSTEM_NAME}")
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(ENABLE_ASAN TRUE)
    endif()
endif()

add_subdirectory(code)