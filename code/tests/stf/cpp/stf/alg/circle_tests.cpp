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

    TEST(circle, canonical_angle)
    {
        std::vector<scaffolding::circle::canonical_angle<float>> tests = 
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
            { 5 * stff::constants::pi, stff::constants::pi },
            { 9 * stff::constants::quarter_pi, stff::constants::quarter_pi },
        };

        for (scaffolding::circle::canonical_angle<float> const& test : tests) { scaffolding::circle::verify(test); }
    }

    TEST(circle, closest_equiv_angle)
    {
        std::vector<scaffolding::circle::closest_equiv_angle<float>> tests = 
        {
            { 0, 0, 0 },
            { 4 * stff::constants::tau, 4 * stff::constants::tau, 4 * stff::constants::tau },
            { 5 * stff::constants::pi, stff::constants::quarter_pi, stff::constants::pi },
            { 6 * stff::constants::tau, 0, 0 },
        };

        for (scaffolding::circle::closest_equiv_angle<float> const& test : tests) { scaffolding::circle::verify(test); }
    }

    TEST(circle, unit_vector)
    {
        std::vector<scaffolding::circle::unit_vector<float>> tests = 
        {
            { 0, stff::vec2(1, 0) },
            { stff::constants::half_pi, stff::vec2(0, 1) },
            { stff::constants::pi, stff::vec2(-1, 0) },
            { 3 * stff::constants::half_pi, stff::vec2(0, -1) },
            { stff::constants::tau, stff::vec2(1, 0) },
            { stff::constants::quarter_pi, stff::vec2(stff::constants::sqrt_two_inv, stff::constants::sqrt_two_inv) },
        };

        for (scaffolding::circle::unit_vector<float> const& test : tests) { scaffolding::circle::verify(test); }
    }

} // math
} // stf