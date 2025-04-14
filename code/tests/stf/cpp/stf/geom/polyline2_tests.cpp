#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/geom/polyline.hpp"

namespace stf::geom
{

    TEST(polyline2, length)
    {
        std::vector<scaffolding::polyline::length<float, 2>> tests =
        {
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(5) }), 5 * stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), 2 * stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0), stff::vec2(1, -1) }), 3 * stff::constants::sqrt_two },
        };

        for (scaffolding::polyline::length<float, 2> const& test : tests)
        {
            scaffolding::polyline::verify(test);
        }
    }

    TEST(polyline2, dist_and_dist_squared)
    {
        std::vector<scaffolding::polyline::dist_and_dist_squared<float, 2>> tests =
        {
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), stff::vec2(0), 0 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(0.5) }), stff::vec2(0), 0 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), stff::vec2(0), 0 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), stff::vec2(0, 1), 1 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), stff::vec2(1, -1), 1 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), stff::vec2(-2, 0), 4 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), stff::vec2(3, 0), 4 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(2, 0), 0 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(0, 1), 0.5 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(1, 0), 0.5 },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(5, 4), 24.5 },
        };

        for (scaffolding::polyline::dist_and_dist_squared<float, 2> const& test : tests)
        {
            scaffolding::polyline::verify(test);
        }
    }

    TEST(polyline2, interpolate)
    {
        std::vector<scaffolding::polyline::interpolate<float, 2>> tests =
        {
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), 0, stff::vec2(0) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), 0.5, stff::vec2(0.5) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), 1, stff::vec2(1, 0) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), -1, stff::vec2(0) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1, 0) }), 2, stff::vec2(1, 0) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), 0.25, stff::vec2(0.5) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), 0.5, stff::vec2(1) },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), 0.75, stff::vec2(1.5, 0.5) },
        };

        for (scaffolding::polyline::interpolate<float, 2> const& test : tests)
        {
            scaffolding::polyline::verify(test);
        }
    }

} // stf::geom