#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/polyline.hpp"

namespace stf::geom
{

    TEST(polyline2, length)
    {
        std::vector<scaffolding::polyline::length<float, 2>> tests =
        {
            { stff::polyline2({ stff::vec2(0), stff::vec2(1) }), stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(5) }), 5 * stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), 2 * stff::constants::sqrt_two },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0), stff::vec2(1, -1) }), 3 * stff::constants::sqrt_two},
        };

        for (scaffolding::polyline::length<float, 2> const& test : tests)
        {
            scaffolding::polyline::verify(test);
        }
    }

} // stf::geom