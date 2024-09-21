#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/segment.hpp"

namespace stf::geom
{

    TEST(segment2, distance)
    {
        std::vector<scaffolding::segment::distance<float, 2>> tests =
        {
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::vec2(0), 0 },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::vec2(0.5), 0 },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::vec2(1), 0 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(0, 1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(0, -1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(-1, 0), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(0.5, 1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(0.5, -1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(1, 1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(1, -1), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(2, 0), 1 },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), stff::vec2(0, 1), math::constants<float>::sqrt_two_inv },
        };

        for (scaffolding::segment::distance<float, 2> const& test : tests)
        {
            scaffolding::segment::verify(test);
        }
    }

    TEST(segment2, interpolate)
    {
        std::vector<scaffolding::segment::interpolate<float, 2>> tests =
        {
            { stff::segment2(stff::vec2(0), stff::vec2(1)), 0, stff::vec2(0) },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), 0.5, stff::vec2(0.5) },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), 1, stff::vec2(1) },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), -1, stff::vec2(0) },
            { stff::segment2(stff::vec2(0), stff::vec2(1)), 1.5, stff::vec2(1) },
            { stff::segment2(stff::vec2(1), stff::vec2(5, 3)), 0, stff::vec2(1) },
            { stff::segment2(stff::vec2(1), stff::vec2(5, 3)), 0.5, stff::vec2(3, 2) },
            { stff::segment2(stff::vec2(1), stff::vec2(5, 3)), 1, stff::vec2(5, 3) },
        };

        for (scaffolding::segment::interpolate<float, 2> const& test : tests)
        {
            scaffolding::segment::verify(test);
        }
    }

} // stf::geom