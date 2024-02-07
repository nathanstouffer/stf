#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/alg/scaffolding/intersection.hpp"

namespace stf::alg
{

    TEST(intersection, segment)
    {
        std::vector<scaffolding::intersection::segment<float>> tests =
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

        for (scaffolding::intersection::segment<float> const& test : tests)
        {
            scaffolding::intersection::verify(test);
        }
    }

} // stf::alg