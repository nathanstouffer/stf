#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/cam/scaffolding/frustum.hpp"

namespace stf::cam
{

    TEST(frustum, contains)
    {
        // camera with the eye at the origin that looks along the +y axis
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
        // true intersections
        {
            // camera with the eye at the origin that looks along the +y axis with the +z axis is the up vector
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            std::vector<scaffolding::frustum::intersects_fast<double>> tests =
            {
                { frustum, stfd::aabb3(stfd::vec3(-1, 1, -1), 2), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), true },       // crosses the far plane
                { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), true },           // crosses the near plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the left plane
                { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), true },          // crosses the right plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), true },          // crosses the top plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the bottom plane
            };

            for (scaffolding::frustum::intersects_fast<double> const& test : tests) { scaffolding::frustum::verify(test); }
        }

        // false positives
        {
            // camera with the eye at the origin that looks along the -z axis with vec3(1, 1, 0) defining the up direction
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_fourths, stfd::constants::pi, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            // TODO (stouff) remove this once we improve the test
            // camera with the eye at the origin that looks along the +y axis with the +z axis is the up vector
            stfd::scamera old_camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum old_frustum(old_camera);

            std::vector<scaffolding::frustum::intersects_fast<double>> tests =
            {
                { old_frustum, stfd::aabb3(stfd::vec3(-610, 90, -10), stfd::vec3(-110, 590, 10)), true },   // TODO (stouff) move this above once we improve the intersection alg
                { frustum, stfd::aabb3(stfd::vec3(-500, 50, -10), stfd::vec3(500, 550, 10)), true },
            };

            for (scaffolding::frustum::intersects_fast<double> const& test : tests) { scaffolding::frustum::verify(test); }
        }
    }

} // stf::cam