#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/aabb.hpp"

namespace stf::geom
{

    TEST(aabb2, intersects)
    {
        std::vector<scaffolding::aabb::intersects<float, 2>> tests =
        {
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(0), stff::vec2(2)), true },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(1), stff::vec2(3)), true },
            { stff::aabb2(stff::vec2(6), stff::vec2(8)), stff::aabb2(stff::vec2(5), stff::vec2(7)), true },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(2), stff::vec2(4)), true },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(3), stff::vec2(4)), false },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(3), stff::vec2(4)), false },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(2.000001), stff::vec2(4)), false },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(-2), stff::vec2(-0.0000001)), false },
        };

        for (scaffolding::aabb::intersects<float, 2> const& test : tests)
        {
            scaffolding::aabb::verify(test);
        }
    }

    TEST(aabb2, contains)
    {
        std::vector<scaffolding::aabb::contains<float, 2>> tests =
        {
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(0), stff::vec2(2)), true },
            { stff::aabb2(stff::vec2(0), stff::vec2(4)), stff::aabb2(stff::vec2(1), stff::vec2(3)), true },
            { stff::aabb2(stff::vec2(1), stff::vec2(3)), stff::aabb2(stff::vec2(0), stff::vec2(4)), false },
            { stff::aabb2(stff::vec2(5), stff::vec2(7)), stff::aabb2(stff::vec2(4), stff::vec2(6)), false },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::aabb2(stff::vec2(5), stff::vec2(7)), false },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::aabb2(stff::vec2(4), stff::vec2(6)), false },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::aabb2(stff::vec2(0), stff::vec2(2)), false },
        };

        for (scaffolding::aabb::contains<float, 2> const& test : tests)
        {
            scaffolding::aabb::verify(test);
        }
    }

} // stf::geom