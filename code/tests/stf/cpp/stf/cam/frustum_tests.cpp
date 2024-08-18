#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/cam/scaffolding/frustum.hpp"

namespace stf::cam
{

    TEST(frustum, contains)
    {
        stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
        stfd::frustum frustum(camera);

        std::vector<scaffolding::frustum::contains<double>> tests =
        {
            { frustum, stfd::aabb3(stfd::vec3(-1, 1, -1), 2), true },
            { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true },
            { frustum, stfd::aabb3(stfd::vec3(110, 90, -50), 100), false },     // entirely outside the frustum
            { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), false },      // crosses the far plane
            { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), false },          // crosses the near plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), false },       // crosses the left plane
            { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), false },         // crosses the right plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), false },         // crosses the top plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), false },       // crosses the bottom plane
        };

        for (scaffolding::frustum::contains<double> const& test : tests) { scaffolding::frustum::verify(test); }
    }

    TEST(frustum, intersects_fast)
    {
        stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
        stfd::frustum frustum(camera);

        std::vector<scaffolding::frustum::intersects_fast<double>> tests =
        {
            { frustum, stfd::aabb3(stfd::vec3(-1, 1, -1), 2), true, false },
            { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true, false },
            { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), true, false },      // crosses the far plane
            { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), true, false },          // crosses the near plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true, false },       // crosses the left plane
            { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), true, false },         // crosses the right plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), true, false },         // crosses the top plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true, false },       // crosses the bottom plane
        };

        for (scaffolding::frustum::intersects_fast<double> const& test : tests) { scaffolding::frustum::verify(test); }
    }

} // stf::cam