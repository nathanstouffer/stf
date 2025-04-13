#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/matrix.hpp"

namespace stf::math
{

    TEST(mtx2, equality)
    {
        std::vector<scaffolding::mtx::equality<float, 2>> tests =
        {
            { stff::mtx2(), stff::mtx2(), true },
            { stff::mtx2(1), stff::mtx2(1), true },
            { stff::mtx2(1), stff::mtx2(2), false },
            { stff::mtx2(stff::vec4(1, 0, 0, 1)), stff::mtx2(stff::vec4(1, 0, 0, 1)), true },
            { stff::mtx2(stff::vec4(1, 0, 0, 1)), stff::mtx2(stff::vec4(1, 0, 0, 1.1f)), false },
        };

        for (scaffolding::mtx::equality<float, 2> const& test : tests) { scaffolding::mtx::verify(test); }
    }

    TEST(mtx2, determinant)
    {
        std::vector<scaffolding::mtx::determinant<float, 2>> tests =
        {
            { stff::mtx2(), 1 },
            { stff::mtx2(stff::vec2(2)), 4 },
            { stff::mtx2(stff::vec2(-2)), 4 },
            { stff::mtx2(stff::vec2(-2, 2)), -4 },
            { stff::mtx2(stff::vec4(2)), 0 },
            { stff::mtx2(stff::vec4({ 2, 1, -3, 5 })), 13 },
        };

        for (scaffolding::mtx::determinant<float, 2> const& test : tests) { scaffolding::mtx::verify(test); }
    }

    TEST(mtx2, inverted)
    {
        std::vector<scaffolding::mtx::inverted<float, 2>> tests =
        {
            { stff::mtx2() },
            { stff::mtx2(stff::vec2(2)) },
            { stff::mtx2(stff::vec2(-2)) },
            { stf::math::rotate<float>(stff::constants::quarter_pi) },
            { stf::math::rotate<float>(stff::constants::half_pi) },
        };

        for (scaffolding::mtx::inverted<float, 2> const& test : tests) { scaffolding::mtx::verify(test); }
    }

} // stf::math