#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/intersection.hpp"

namespace stf::alg
{

    TEST(intersection, segment_with_segment)
    {
        std::vector<scaffolding::intersection::segment_with_segment<float>> tests =
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

        for (scaffolding::intersection::segment_with_segment<float> const& test : tests)
        {
            scaffolding::intersection::verify(test);
        }
    }

    TEST(intersection, segment_with_aabb)
    {
        stff::aabb2 box(stff::vec2(0), stff::vec2(10));
        std::vector<scaffolding::intersection::segment_with_aabb<float>> tests =
        {
            // segments inside the box
            { stff::segment2(stff::vec2(1), stff::vec2(2)), box, true },
            { stff::segment2(stff::vec2(3, 2), stff::vec2(8, 2)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(10)), box, true },
            // segments on the intersecting on the edge of the box
            { stff::segment2(stff::vec2(0), stff::vec2(10, 0)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), box, true },
            { stff::segment2(stff::vec2(0), stff::vec2(5, -1)), box, true },
            { stff::segment2(stff::vec2(10, 10), stff::vec2(11, 9)), box, true },
            { stff::segment2(stff::vec2(9, 11), stff::vec2(11, 9)), box, true },
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

        for (scaffolding::intersection::segment_with_aabb<float> const& test : tests)
        {
            scaffolding::intersection::verify(test);
        }
    }

} // stf::alg