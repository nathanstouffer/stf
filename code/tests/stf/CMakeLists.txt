enable_testing()

set(TEST_FILES_PREFIX "cpp/stf")

set(TEST_FILES
    ${TEST_FILES_PREFIX}/alg/interpolation_tests.cpp
    ${TEST_FILES_PREFIX}/alg/transform_tests.cpp
    ${TEST_FILES_PREFIX}/cam/scamera_tests.cpp
    ${TEST_FILES_PREFIX}/gfx/color_tests.cpp
    ${TEST_FILES_PREFIX}/math/aabb2_tests.cpp
    ${TEST_FILES_PREFIX}/math/mtx4_tests.cpp
    ${TEST_FILES_PREFIX}/math/crange_tests.cpp
    ${TEST_FILES_PREFIX}/math/range_tests.cpp
    ${TEST_FILES_PREFIX}/math/spherical_tests.cpp
    ${TEST_FILES_PREFIX}/math/vec2_tests.cpp
    ${TEST_FILES_PREFIX}/math/vec3_tests.cpp
    ${TEST_FILES_PREFIX}/math/vec4_tests.cpp
    ${TEST_FILES_PREFIX}/math/vec5_tests.cpp
)

add_executable(tests ${TEST_FILES})

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/private)

target_link_libraries(tests PRIVATE stf GTest::gtest_main)

# set up cpp files with precompiled headers
# TODO (stouff) consider adding <stf/types.hpp> to this list
target_precompile_headers(tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)
# finds all the tests associated with the executable
gtest_discover_tests(tests)