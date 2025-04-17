#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/geom/obb.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::geom
{

    TEST(obb2, from_aabb)
    {
        std::vector<scaffolding::geom::obb::from_aabb<float, 2>> tests =
        {
            { stff::aabb2(stff::vec2(0), stff::vec2(1)) },
            { stff::aabb2(stff::vec2(1, 4), stff::vec2(2, 8)) },
        };
        scaffolding::verify(tests);
    }

    TEST(obb2, extremity)
    {
        // simple tests
        std::vector<scaffolding::geom::obb::extremity<float, 2>> tests =
        {
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::vec2(1, 1), stff::vec2(1, 1) },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::vec2(1, -1), stff::vec2(1, 0) },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::vec2(-1, 1), stff::vec2(0, 1) },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::vec2(-1, -1), stff::vec2(0, 0) },
        };

        // add more complex tests
        {
            {
                stff::vec2 center(0.f);
                stff::mtx2 rotation = stf::math::rotate(stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(center, rotation, stff::vec2(1)), stff::vec2(1, 0), stff::vec2(stff::constants::sqrt_two, 0) });
            }
            {
                stff::vec2 center(0.f);
                stff::mtx2 rotation = stf::math::rotate(stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(center, rotation, stff::vec2(1)), stff::vec2(0, 1), stff::vec2(0, stff::constants::sqrt_two) });
            }
            {
                stff::vec2 center(0.f);
                stff::mtx2 rotation = stf::math::rotate(stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(center, rotation, stff::vec2(1)), stff::vec2(-1, 0), stff::vec2(-stff::constants::sqrt_two, 0) });
            }
            {
                stff::vec2 center(0.f);
                stff::mtx2 rotation = stf::math::rotate(stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(center, rotation, stff::vec2(1)), stff::vec2(0, -1), stff::vec2(0, -stff::constants::sqrt_two) });
            }
        }

        scaffolding::verify(tests);
    }

    TEST(obb2, intersect)
    {
        // simple tests
        std::vector<scaffolding::geom::obb::intersect<float, 2>> tests =
        {
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), true },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(stff::aabb2(stff::vec2(1), stff::vec2(2))), true },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(stff::aabb2(stff::vec2(2), stff::vec2(2))), false },
            { stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(stff::aabb2(stff::vec2(2), stff::vec2(3))), false },
        };

        // add more complex tests
        {
            {
                stff::vec2 center(0.5f);
                stff::mtx2 rotation = stf::math::rotate(stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(center, rotation, stff::vec2(1)), true });
            }
            {
                stff::vec2 center(5);
                stff::mtx2 rotation = stf::math::rotate(-stff::constants::quarter_pi);
                tests.push_back({ stff::obb2(stff::aabb2(stff::vec2(0), stff::vec2(1))), stff::obb2(center, rotation, stff::vec2(5 * stff::constants::sqrt_two, 1)), false });
            }
        }

        scaffolding::verify(tests);
    }

} // stf::geom