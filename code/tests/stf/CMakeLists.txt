enable_testing()

add_executable(tests
    "cpp/stf/alg/intersection_tests.cpp"
    "cpp/stf/cam/scamera_tests.cpp"
    "cpp/stf/geom/aabb2_tests.cpp"
    "cpp/stf/geom/segment2_tests.cpp"
    "cpp/stf/gfx/color_tests.cpp"
    "cpp/stf/math/mtx4_tests.cpp"
    "cpp/stf/math/crange_tests.cpp"
    "cpp/stf/math/interpolation_tests.cpp"
    "cpp/stf/math/range_tests.cpp"
    "cpp/stf/math/spherical_tests.cpp"
    "cpp/stf/math/transform_tests.cpp"
    "cpp/stf/math/vec2_tests.cpp"
    "cpp/stf/math/vec3_tests.cpp"
    "cpp/stf/math/vec4_tests.cpp"
    "cpp/stf/math/vec5_tests.cpp"
    "include/private/stf/alg/scaffolding/intersection.hpp"
    "include/private/stf/cam/scaffolding/scamera.hpp"
    "include/private/stf/geom/scaffolding/aabb.hpp"
    "include/private/stf/geom/scaffolding/segment.hpp"
    "include/private/stf/gfx/scaffolding/color.hpp"
    "include/private/stf/math/scaffolding/crange.hpp"
    "include/private/stf/math/scaffolding/interpolation.hpp"
    "include/private/stf/math/scaffolding/range.hpp"
    "include/private/stf/math/scaffolding/spherical.hpp"
    "include/private/stf/math/scaffolding/transform.hpp"
    "include/private/stf/math/scaffolding/vector.hpp"
)

target_include_directories(tests PRIVATE "include/private")

target_link_libraries(tests PRIVATE stf GTest::gtest_main)

# set up cpp files with precompiled headers
# TODO consider adding <stf/stf.hpp> to this list
target_precompile_headers(tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)
# finds all the tests associated with the executable
gtest_discover_tests(tests)