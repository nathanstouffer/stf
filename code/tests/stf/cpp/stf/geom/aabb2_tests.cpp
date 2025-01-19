#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/aabb.hpp"

namespace stf::geom
{

    TEST(aabb2, cast)
    {
        std::vector<scaffolding::aabb::cast<float, double, 2>> tests =
        {
            { stff::aabb2(stff::vec2(0), stff::vec2(1)) },
            { stff::aabb2(stff::vec2(1.f, 2.f), stff::vec2(2.f, 5.f)) },
            { stff::aabb2(stff::vec2(1.f), stff::vec2(2.f)) },
            { stff::aabb2(stff::vec2(4.f), stff::vec2(10.f)) },
        };

        for (scaffolding::aabb::cast<float, double, 2> const& test : tests) { scaffolding::aabb::verify(test); }
    }

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

    TEST(aabb2, dist_and_dist_squared)
    {
        std::vector<scaffolding::aabb::dist_and_dist_squared<float, 2>> tests =
        {
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::vec2(1), 0 },
            { stff::aabb2(stff::vec2(0), stff::vec2(4)), stff::vec2(0), 0 },
            { stff::aabb2(stff::vec2(1), stff::vec2(3)), stff::vec2(3), 0 },
            { stff::aabb2(stff::vec2(5), stff::vec2(7)), stff::vec2(5, 7), 0 },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::vec2(6, 4), 0 },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::vec2(7, 5), 1 },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::vec2(6, 8), 4 },
            { stff::aabb2(stff::vec2(4), stff::vec2(6)), stff::vec2(4, 2), 4 },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::vec2(3), 2 },
            { stff::aabb2(stff::vec2(0), stff::vec2(2)), stff::vec2(-1), 2 },
        };

        for (scaffolding::aabb::dist_and_dist_squared<float, 2> const& test : tests)
        {
            scaffolding::aabb::verify(test);
        }
    }

} // stf::geom