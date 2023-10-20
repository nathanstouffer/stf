set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

if (BUILD_TESTS)
    include(CTest)
endif()

add_subdirectory(src)
add_subdirectory(deps)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()