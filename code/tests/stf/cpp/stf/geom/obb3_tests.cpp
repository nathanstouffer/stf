#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/obb.hpp"

namespace stf::geom
{

    TEST(obb3, from_aabb)
    {
        std::vector<scaffolding::obb::from_aabb<float, 3>> tests =
        {
            { stff::aabb3(stff::vec3(0), stff::vec3(1)) },
            { stff::aabb3(stff::vec3(1, 4, -5), stff::vec3(2, 8, -1)) },
        };

        for (scaffolding::obb::from_aabb<float, 3> const& test : tests)
        {
            scaffolding::obb::verify(test);
        }
    }

    TEST(obb3, fit)
    {
        std::vector<scaffolding::obb::fit<float, 3>> tests =
        {
            { stf::math::rotate_z(stff::constants::quarter_pi).prefix() * stf::math::rotate_y(-stff::constants::quarter_pi).prefix(), stff::constants::sqrt_two },
        };

        for (scaffolding::obb::fit<float, 3> const& test : tests)
        {
            scaffolding::obb::verify(test);
        }
    }

    TEST(obb3, contains)
    {
        std::vector<scaffolding::obb::contains<float, 3>> tests =
        {
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(0), true },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(5), true },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(10), true },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(-1), false },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(11, 5, 5), false },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(5, 11, 5), false },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(10))), stff::vec3(5, 5, 11), false },
        };

        for (scaffolding::obb::contains<float, 3> const& test : tests)
        {
            scaffolding::obb::verify(test);
        }
    }

    TEST(obb3, intersect)
    {
        // simple tests
        std::vector<scaffolding::obb::intersect<float, 3>> tests =
        {
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), true },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(stff::aabb3(stff::vec3(1), stff::vec3(2))), true },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(stff::aabb3(stff::vec3(2), stff::vec3(2))), false },
            { stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(stff::aabb3(stff::vec3(2), stff::vec3(3))), false },
        };

        // add more complex tests
        {
            {
                stff::vec3 center(0.5f);
                float quarter_pi = stff::constants::quarter_pi;
                stff::mtx4 rotation = stf::math::rotate_z(quarter_pi) * stf::math::rotate_y(-quarter_pi);
                tests.push_back({ stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(center, rotation.prefix(), stff::vec3(1)), true });
            }
            {
                stff::vec3 center(5);
                float quarter_pi = stff::constants::quarter_pi;
                stff::mtx4 rotation = stf::math::rotate_z(quarter_pi) * stf::math::rotate_y(-quarter_pi);
                float half_extent = 5 * stff::constants::sqrt_two;
                tests.push_back({ stff::obb3(stff::aabb3(stff::vec3(0), stff::vec3(1))), stff::obb3(center, rotation.prefix(), stff::vec3(1, half_extent, half_extent)), false });
            }
            {
                stff::vec3 center0(0);
                stff::mtx4 rotation0 = stf::math::rotate_x(stff::constants::half_pi) * stf::math::rotate_z(stff::constants::quarter_pi);
                stff::obb3 box0(center0, rotation0.prefix(), stff::vec3(1));

                stff::vec3 center1(0, 0, 2 * stff::constants::sqrt_two + 0.001f);
                stff::mtx4 rotation1 = stf::math::rotate_x(stff::constants::quarter_pi);

                tests.push_back({ box0, stff::obb3(center1 - stff::vec3(0, 0, 0.001f), rotation1.prefix(), stff::vec3(1)), true });
                tests.push_back({ box0, stff::obb3(center1 + stff::vec3(0, 0, 0.001f), rotation1.prefix(), stff::vec3(1)), false });
            }
        }

        for (scaffolding::obb::intersect<float, 3> const& test : tests)
        {
            scaffolding::obb::verify(test);
        }
    }

} // stf::geom