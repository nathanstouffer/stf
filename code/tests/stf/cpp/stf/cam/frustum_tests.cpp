#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/cam/scaffolding/frustum.hpp"

namespace stf::cam
{

    TEST(frustum, intersects_fast)
    {
        stff::scamera camera(stff::vec3(0), stff::constants::pi_halves, stff::constants::pi_halves, 0.1f, 100.f);
        stff::frustum frustum(camera);

        std::vector<scaffolding::frustum::intersects_fast<float>> tests =
        {
            { frustum, stff::aabb3(stff::vec3(-1, 1, -1), stff::vec3(1, 1, 1)), true, false },
        };

        for (scaffolding::frustum::intersects_fast<float> const& test : tests) { scaffolding::frustum::verify(test); }
    }

} // stf::cam