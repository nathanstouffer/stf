list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (BUILD_TESTS)
    include(CTest)
    include(CoverageBuildType)
endif()

add_subdirectory(deps)
add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_DOCS)
    include(GenerateDocs)
endif()