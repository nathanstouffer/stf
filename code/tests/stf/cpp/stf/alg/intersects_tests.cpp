#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/intersects.hpp"

namespace stf::alg
{

    TEST(intersects, segment_with_segment)
    {
        std::vector<scaffolding::intersects::segment_with_segment<float>> tests =
        {
            // colinear segments that intersect
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0), stff::vec2(1)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0.5), stff::vec2(1)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0), stff::vec2(0.5)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0.25), stff::vec2(0.75)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(-1), stff::vec2(2)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0.5), stff::vec2(2)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(-2), stff::vec2(0.5)), true },
            // colinear segments that do not intersect
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(2), stff::vec2(4)), false },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(-2), stff::vec2(-4)), false },
            // non colinear segments that intersect
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0, 1), stff::vec2(1, 0)), true },
            { stff::segment2(stff::vec2(4), stff::vec2(8, 0)), stff::segment2(stff::vec2(6, 2), stff::vec2(1, 0)), true },
            { stff::segment2(stff::vec2(4), stff::vec2(8, 0)), stff::segment2(stff::vec2(0, 2), stff::vec2(10, 2)), true },
            { stff::segment2(stff::vec2(0), stff::vec2(5)), stff::segment2(stff::vec2(0, -2), stff::vec2(0, 2)), true },
            // non colinear segments that do not intersect
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::segment2(stff::vec2(0, -1), stff::vec2(1, 0)), false },
            { stff::segment2(stff::vec2(4), stff::vec2(8, 0)), stff::segment2(stff::vec2(5.99999, 2), stff::vec2(1, 0)), false },
            { stff::segment2(stff::vec2(0), stff::vec2(5)), stff::segment2(stff::vec2(-2, 0), stff::vec2(2, -2)), false },
            { stff::segment2(stff::vec2(0), stff::vec2(5)), stff::segment2(stff::vec2(-0.00001, -2), stff::vec2(0, 2)), false },
        };

        for (scaffolding::intersects::segment_with_segment<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, segment_with_aabb)
    {
        stff::aabb2 box(stff::vec2(0), stff::vec2(10));
        std::vector<scaffolding::intersects::segment_with_aabb<float>> tests =
        {
            // segments inside the box
            { stff::segment2(stff::vec2(1), stff::vec2(2)), box, true },
            { stff::segment2(stff::vec2(3, 2), stff::vec2(8, 2)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(10)), box, true },
            // segments on the edge of the box
            { stff::segment2(stff::vec2(0), stff::vec2(10, 0)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(5, -1)), box, true },
            { stff::segment2(stff::vec2(10, 10), stff::vec2(11, 9)), box, true },
            { stff::segment2(stff::vec2(9, 11), stff::vec2(11, 9)), box, true },
            { stff::segment2(stff::vec2(10, 9), stff::vec2(11, 9)), box, true },
            // segments crossing the boundary of the box
            { stff::segment2(stff::vec2(5, 5), stff::vec2(11, 5)), box, true },
            { stff::segment2(stff::vec2(5, 5), stff::vec2(5, 11)), box, true },
            { stff::segment2(stff::vec2(5, 5), stff::vec2(-11, 5)), box, true },
            { stff::segment2(stff::vec2(5, 5), stff::vec2(5, -11)), box, true },
            { stff::segment2(stff::vec2(5, 5), stff::vec2(11, 11)), box, true },
            { stff::segment2(stff::vec2(5, 5), stff::vec2(-11, -11)), box, true },
            // segments outside the box
            { stff::segment2(stff::vec2(0, -5), stff::vec2(10, -5)), box, false },
            { stff::segment2(stff::vec2(0, 15), stff::vec2(10, 15)), box, false },
            { stff::segment2(stff::vec2(0, -0.000001), stff::vec2(10, -0.000001)), box, false },
            { stff::segment2(stff::vec2(-0.000001, 0), stff::vec2(-0.000001, 10)), box, false },
            { stff::segment2(stff::vec2(9, 11.00001), stff::vec2(11.00001, 9)), box, false },
        };

        for (scaffolding::intersects::segment_with_aabb<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, polyline_with_aabb)
    {
        stff::aabb2 box(stff::vec2(0), stff::vec2(10));
        std::vector<scaffolding::intersects::polyline_with_aabb<float>> tests =
        {
            // polylines contained in the box
            { stff::polyline2({ stff::vec2(1), stff::vec2(2), stff::vec2(5, 6) }), box, true },
            { stff::polyline2({ stff::vec2(9), stff::vec2(2), stff::vec2(3, 6) }), box, true },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(10, 0) }), box, true },
            // polylines crossing the boundary
            { stff::polyline2({ stff::vec2(1), stff::vec2(11), stff::vec2(15, 5) }), box, true },
            { stff::polyline2({ stff::vec2(1), stff::vec2(-1, 4), stff::vec2(5) }), box, true },
            // polylines touching only the boundary
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, -1), stff::vec2(10, 0) }), box, true },
            { stff::polyline2({ stff::vec2(0), stff::vec2(10, 0), stff::vec2(10) }), box, true },
            { stff::polyline2({ stff::vec2(9, -1), stff::vec2(11, 1) }), box, true },
            // polylines outside the box
            { stff::polyline2({ stff::vec2(-1), stff::vec2(-1, 5), stff::vec2(-5) }), box, false },
            { stff::polyline2({ stff::vec2(9, -1.00001), stff::vec2(11, 0.99999) }), box, false },
            { stff::polyline2({ stff::vec2(-0.00001), stff::vec2(-0.00001, 10.00001), stff::vec2(10.00001) }), box, false},
        };

        for (scaffolding::intersects::polyline_with_aabb<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, polygon_with_aabb)
    {
        stff::aabb2 box(stff::vec2(0), stff::vec2(10));
        std::vector<scaffolding::intersects::polygon_with_aabb<float>> tests =
        {
            // polygons contained in the box
            { stff::polygon({ stff::vec2(1), stff::vec2(5), stff::vec2(4, 3) }), box, true },
            // polygons containing the box
            { stff::polygon({ stff::vec2(-1), stff::vec2(-1, 11), stff::vec2(12, 15), stff::vec2(15, -5) }), box, true },
            // polygons crossing the boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(5), stff::vec2(6, -1) }), box, true },
            { stff::polygon({ stff::vec2(-1, 5), stff::vec2(5), stff::vec2(4, 2) }), box, true },
            // polygons touching only the boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(0), stff::vec2(0, -1) }), box, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(10, 0), stff::vec2(5, -5) }), box, true },
            // polygons outside the box
            { stff::polygon({ stff::vec2(-1), stff::vec2(-5), stff::vec2(-5, 0) }), box, false },
            { stff::polygon({ stff::vec2(-11, 10), stff::vec2(-0.000001, 10), stff::vec2(-0.000001), stff::vec2(10, -0.000001), stff::vec2(10, -11) }), box, false},
        };

        for (scaffolding::intersects::polygon_with_aabb<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, polygon_with_segment)
    {
        std::vector<scaffolding::intersects::polygon_with_segment<float>> tests =
        {
            // segment inside polygon
            { stff::polygon({ stff::vec2(0), stff::vec2(5), stff::vec2(5, 0) }), stff::segment2(stff::vec2(2, 1), stff::vec2(4, 3)), true },
            { stff::polygon({ stff::vec2(-1), stff::vec2(-1, 11), stff::vec2(12, 15), stff::vec2(15, -5) }), stff::segment2(stff::vec2(10, 2), stff::vec2(3, 8)), true },
            // segment crossing polygon boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(5), stff::vec2(6, -1) }), stff::segment2(stff::vec2(0, 4), stff::vec2(3, 2)), true },
            { stff::polygon({ stff::vec2(-1, 5), stff::vec2(5), stff::vec2(4, 2) }), stff::segment2(stff::vec2(3, 8), stff::vec2(3, 4)), true },
            // segment touching only polygon boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(0), stff::vec2(0, -1) }), stff::segment2(stff::vec2(-1), stff::vec2(0)), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(10, 0), stff::vec2(5, -5) }), stff::segment2(stff::vec2(5, 0), stff::vec2(8, 0)), true },
            // segments outside polygon
            { stff::polygon({ stff::vec2(-1), stff::vec2(-5), stff::vec2(-5, 0) }), stff::segment2(stff::vec2(2), stff::vec2(9, 0)), false },
            { stff::polygon({ stff::vec2(-1), stff::vec2(-5), stff::vec2(-5, 0) }), stff::segment2(stff::vec2(-4, -5), stff::vec2(-2, -3)), false },
        };

        for (scaffolding::intersects::polygon_with_segment<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, polygon_with_polyline)
    {
        std::vector<scaffolding::intersects::polygon_with_polyline<float>> tests =
        {
            // polyline inside polygon
            { stff::polygon({ stff::vec2(0), stff::vec2(5), stff::vec2(5, 0) }), stff::polyline2({ stff::vec2(2, 1), stff::vec2(4, 3) }), true },
            { stff::polygon({ stff::vec2(-1), stff::vec2(-1, 11), stff::vec2(12, 15), stff::vec2(15, -5) }), stff::polyline2({ stff::vec2(10, 2), stff::vec2(3, 8) }), true },
            // polyline crossing polygon boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(5), stff::vec2(6, -1) }), stff::polyline2({ stff::vec2(0, 4), stff::vec2(3, 2) }), true },
            { stff::polygon({ stff::vec2(-1, 5), stff::vec2(5), stff::vec2(4, 2) }), stff::polyline2({ stff::vec2(3, 8), stff::vec2(3, 4) }), true },
            // polyline touching only polygon boundary
            { stff::polygon({ stff::vec2(-1), stff::vec2(0), stff::vec2(0, -1) }), stff::polyline2({ stff::vec2(-1), stff::vec2(0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(10, 0), stff::vec2(5, -5) }), stff::polyline2({ stff::vec2(5, 0), stff::vec2(8, 0) }), true },
            // polyline outside polygon
            { stff::polygon({ stff::vec2(-1), stff::vec2(-5), stff::vec2(-5, 0) }), stff::polyline2({ stff::vec2(2), stff::vec2(9, 0) }), false },
            { stff::polygon({ stff::vec2(-1), stff::vec2(-5), stff::vec2(-5, 0) }), stff::polyline2({ stff::vec2(-4, -5), stff::vec2(-2, -3) }), false },
        };

        for (scaffolding::intersects::polygon_with_polyline<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

    TEST(intersects, ray_with_plane)
    {
        std::vector<scaffolding::intersects::ray_with_plane<float>> tests =
        {
            // ray that is a subset of plane
            { stff::ray3(stff::vec3(), stff::vec3(1, 0, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)), true },
            { stff::ray3(stff::vec3(), stff::vec3(1, 1, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)), true },
            { stff::ray3(stff::vec3(), stff::vec3(0, 0, 1)), stff::plane(stff::vec3(), stff::vec3(1, 0, 0)), true },
            // ray that is parallel to plane
            { stff::ray3(stff::vec3(0, 0, 1), stff::vec3(1, 0, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)), false },
            { stff::ray3(stff::vec3(-1, 0, 0), stff::vec3(0, 0, 1)), stff::plane(stff::vec3(), stff::vec3(1, 0, 0)), false },
            // ray is pointing towards plane, normal is pointing towards ray origin
            // ray is pointing towards plane, normal is pointing away from ray origin
            // ray is pointing away from plane, normal is pointing towards ray origin
            // ray is pointing away from plane, normal is pointing towards ray origin
        };

        for (scaffolding::intersects::ray_with_plane<float> const& test : tests)
        {
            scaffolding::intersects::verify(test);
        }
    }

} // stf::alg