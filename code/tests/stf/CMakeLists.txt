enable_testing()

set(STF_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/alg/clipping_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/alg/intersect_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/alg/intersects_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/alg/statistics_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/alg/tessellation_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/ds/indexed_list_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/cam/frustum_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/cam/scamera_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/enums_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/aabb2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/segment2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/obb2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/obb3_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/polygon_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/polyline2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/ray2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/geom/sphere_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/gfx/color_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/mtx2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/mtx3_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/mtx4_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/cinterval_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/interpolation_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/interval_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/spherical_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/transform_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/vec2_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/vec3_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/vec4_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/math/vec5_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/stf/spatial/interval_tree_tests.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/alg/scaffolding/clipping.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/alg/scaffolding/intersect.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/alg/scaffolding/intersects.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/alg/scaffolding/statistics.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/alg/scaffolding/tessellation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/ds/scaffolding/indexed_list.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/cam/scaffolding/frustum.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/cam/scaffolding/scamera.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/aabb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/obb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/polygon.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/polyline.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/ray.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/segment.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/geom/scaffolding/hypersphere.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/gfx/scaffolding/color.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/cinterval.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/interpolation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/interval.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/matrix.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/spherical.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/transform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/math/scaffolding/vector.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/stf/spatial/scaffolding/interval_tree.hpp"
)

add_executable(tests ${STF_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${STF_TEST_FILES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # increase warning level
    target_compile_options(tests PRIVATE
        "-Wall"
        "-Wextra"
        "-Wpedantic"
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # increase warning level
    target_compile_options(tests PRIVATE
        "/W4"
    )
endif()

if(STF_TESTS_WARNINGS_AS_ERROR)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(tests PRIVATE
            "-Werror"
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(tests PRIVATE
            "/WX"
        )
    endif()
endif()

target_include_directories(tests PRIVATE "include/private")

target_link_libraries(tests PRIVATE stf GTest::gtest_main)

# set up cpp files with precompiled headers
# TODO consider adding <stf/stf.hpp> to this list
target_precompile_headers(tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)
# finds all the tests associated with the executable
gtest_discover_tests(tests)