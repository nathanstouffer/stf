#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/cam/frustum.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::cam
{

    TEST(frustum, contains)
    {
        // camera with the eye at the origin that looks along the +y axis
        stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
        stfd::frustum frustum(camera);

        double eps = 1.0E-14;   // slightly inset the box because some compilers have slight differences in floating point precision
        std::vector<scaffolding::cam::frustum::contains<double>> tests =
        {
            { frustum, stfd::aabb3(stfd::vec3(-1 + eps, 1 + eps, -1 - eps), 2 - 2.0 * eps), true }, // slightly inset the box
            { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true },
            { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), false },      // crosses the far plane
            { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), false },          // crosses the near plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), false },       // crosses the left plane
            { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), false },         // crosses the right plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), false },         // crosses the top plane
            { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), false },       // crosses the bottom plane
            { frustum, stfd::aabb3(stfd::vec3(110, 90, -50), 100), false },     // entirely outside the frustum
        };
        scaffolding::verify(tests);
    }

    TEST(frustum, intersects_fast)
    {
        // true intersections
        {
            // camera with the eye at the origin that looks along the +y axis with the +z axis is the up vector
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            std::vector<scaffolding::cam::frustum::intersects_fast<double>> tests =
            {
                { frustum, stfd::aabb3(stfd::vec3(-1, 1, -1), 2), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), true },       // crosses the far plane
                { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), true },           // crosses the near plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the left plane
                { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), true },          // crosses the right plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), true },          // crosses the top plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the bottom plane
                { frustum, stfd::aabb3(stfd::vec3(110, 90, -50), 100), false },     // entirely outside the frustum
                { frustum, stfd::aabb3(stfd::vec3(-610, 90, -10), stfd::vec3(-110, 590, 10)), false },
            };
            scaffolding::verify(tests);
        }

        // false positives
        {
            // camera with the eye at the origin that looks along the -z axis with vec3(1, 1, 0) defining the up direction
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_fourths, stfd::constants::pi, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            std::vector<scaffolding::cam::frustum::intersects_fast<double>> tests =
            {
                { frustum, stfd::aabb3(stfd::vec3(-500, 50, -10), stfd::vec3(500, 550, 10)), true },
            };
            scaffolding::verify(tests);
        }
    }

    TEST(frustum, intersects)
    {
        {
            // camera with the eye at the origin that looks along the +y axis with the +z axis is the up vector
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_halves, stfd::constants::pi_halves, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            std::vector<scaffolding::cam::frustum::intersects<double>> tests =
            {
                { frustum, stfd::aabb3(stfd::vec3(-1, 1, -1), 2), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 50, -10), 20), true },
                { frustum, stfd::aabb3(stfd::vec3(-10, 90, -10), 20), true },       // crosses the far plane
                { frustum, stfd::aabb3(stfd::vec3(-1, 0, -1), 2), true },           // crosses the near plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the left plane
                { frustum, stfd::aabb3(stfd::vec3(0, 5, -10), 20), true },          // crosses the right plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, 0), 20), true },          // crosses the top plane
                { frustum, stfd::aabb3(stfd::vec3(-10, 5, -10), 20), true },        // crosses the bottom plane
                { frustum, stfd::aabb3(stfd::vec3(110, 90, -50), 100), false },     // entirely outside the frustum
                { frustum, stfd::aabb3(stfd::vec3(-610, 90, -10), stfd::vec3(-110, 590, 10)), false },
            };
            scaffolding::verify(tests);
        }

        {
            // camera with the eye at the origin that looks along the -z axis with vec3(1, 1, 0) defining the up direction
            stfd::scamera camera(stfd::vec3(0), stfd::constants::pi_fourths, stfd::constants::pi, 1.0, 100.0, 1.0, stfd::constants::pi_halves);
            stfd::frustum frustum(camera);

            std::vector<scaffolding::cam::frustum::intersects<double>> tests =
            {
                { frustum, stfd::aabb3(stfd::vec3(-500, 50, -10), stfd::vec3(500, 550, 10)), false },
            };
            scaffolding::verify(tests);
        }
    }

} // stf::cam