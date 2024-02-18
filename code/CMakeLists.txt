if (BUILD_TESTS)
    include(CTest)
    include(CoverageBuildType)
endif()

add_subdirectory(deps)
add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()