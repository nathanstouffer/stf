#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/alg/scaffolding/circle.hpp"

namespace stf {
namespace alg {

    TEST(circle, conversion)
    {
        std::vector<scaffolding::circle::conversion<float>> tests = 
        {
            { 0, 0 },
            { stff::constants::quarter_pi, 45.f },
            { stff::constants::half_pi, 90.f },
            { stff::constants::pi, 180.f },
            { stff::constants::tau, 360.f },
        };

        for (scaffolding::circle::conversion<float> const& test : tests) { scaffolding::circle::verify(test); }
    }

    TEST(circle, canonical)
    {
        std::vector<scaffolding::circle::canonical<float>> tests = 
        {
            { 0, 0 },
            { stff::constants::quarter_pi, stff::constants::quarter_pi },
            { stff::constants::half_pi, stff::constants::half_pi },
            { stff::constants::pi, stff::constants::pi },
            { stff::constants::tau, 0 },
            { 1 * stff::constants::tau, 0 },
            { 2 * stff::constants::tau, 0 },
            { -1 * stff::constants::tau, 0 },
            { -2 * stff::constants::tau, 0 },
            { 9 * stff::constants::quarter_pi, stff::constants::quarter_pi },
        };

        for (scaffolding::circle::canonical<float> const& test : tests) { scaffolding::circle::verify(test); }
    };

} // math
} // stf