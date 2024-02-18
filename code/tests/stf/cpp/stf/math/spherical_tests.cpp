#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/spherical.hpp"

namespace stf::math
{

    TEST(spherical, conversion)
    {
        std::vector<scaffolding::spherical::conversion<float>> tests = 
        {
            { 0, 0 },
            { stff::constants::quarter_pi, 45.f },
            { stff::constants::half_pi, 90.f },
            { stff::constants::pi, 180.f },
            { stff::constants::tau, 360.f },
        };

        for (scaffolding::spherical::conversion<float> const& test : tests) { scaffolding::spherical::verify(test); }
    }

    TEST(spherical, canonical_angle)
    {
        std::vector<scaffolding::spherical::canonical_angle<float>> tests = 
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

        for (scaffolding::spherical::canonical_angle<float> const& test : tests) { scaffolding::spherical::verify(test); }
    }

    TEST(spherical, closest_equiv_angle)
    {
        std::vector<scaffolding::spherical::closest_equiv_angle<float>> tests = 
        {
            { 0, 0, 0 },
            { 4 * stff::constants::tau, 4 * stff::constants::tau, 4 * stff::constants::tau },
            { 5 * stff::constants::pi, stff::constants::quarter_pi, stff::constants::pi },
            { 6 * stff::constants::tau, 0, 0 },
        };

        for (scaffolding::spherical::closest_equiv_angle<float> const& test : tests) { scaffolding::spherical::verify(test); }
    }

    TEST(spherical, unit_vector)
    {
        std::vector<scaffolding::spherical::unit_vec2<float>> tests = 
        {
            { 0, stff::vec2(1, 0) },
            { stff::constants::half_pi, stff::vec2(0, 1) },
            { stff::constants::pi, stff::vec2(-1, 0) },
            { 3 * stff::constants::half_pi, stff::vec2(0, -1) },
            { stff::constants::tau, stff::vec2(1, 0) },
            { stff::constants::quarter_pi, stff::vec2(stff::constants::sqrt_two_inv, stff::constants::sqrt_two_inv) },
        };

        for (scaffolding::spherical::unit_vec2<float> const& test : tests) { scaffolding::spherical::verify(test); }
    }

} // stf::math