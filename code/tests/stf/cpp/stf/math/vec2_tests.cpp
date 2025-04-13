#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/vector.hpp"

namespace stf::math
{

    TEST(vec2, index)
    {
        std::vector<scaffolding::vec::read<float, 2>> tests =
        {
            { stff::vec2(), { 0.f, 0.f } },
            { stff::vec2(1.f), { 1.f, 1.f } },
            { stff::vec2(1.f, 2.f), { 1.f, 2.f } },
        };

        for (scaffolding::vec::read<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, write)
    {
        std::vector<scaffolding::vec::write<float, 2>> tests =
        {
            { stff::vec2(), 0, 8.f },
            { stff::vec2(1.f, 2.f), 0, 10.f },
            { stff::vec2(1.f), 1, -5.f },
        };

        for (scaffolding::vec::write<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, add)
    {
        std::vector<scaffolding::vec::add<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), stff::vec2() },
            { stff::vec2(), stff::vec2(1, 6), stff::vec2(1, 6) },
            { stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(5, 9) },
            { stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-4, -1) },
        };

        for (scaffolding::vec::add<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, subtract)
    {
        std::vector<scaffolding::vec::subtract<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), stff::vec2() },
            { stff::vec2(), stff::vec2(1, 6), stff::vec2(-1, -6) },
            { stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(3, -3) },
            { stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-6, -5) },
        };

        for (scaffolding::vec::subtract<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, scale)
    {
        std::vector<scaffolding::vec::scale<float, 2>> tests =
        {
            { stff::vec2(), 0, stff::vec2() },
            { stff::vec2(), 1, stff::vec2() },
            { stff::vec2(1, -1), 1, stff::vec2(1, -1) },
            { stff::vec2(1, -1), -1, stff::vec2(-1, 1) },
            { stff::vec2(1, -1), -2, stff::vec2(-2, 2) },
            { stff::vec2(2, -3), -2, stff::vec2(-4, 6) },
        };

        for (scaffolding::vec::scale<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, dot)
    {
        std::vector<scaffolding::vec::dot<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), 0 },
            { stff::vec2(1), stff::vec2(1), 2 },
            { stff::vec2(1, 4), stff::vec2(4, 1), 8 },
            { stff::vec2(1, -4), stff::vec2(4, 1), 0 },
            { stff::vec2(1, -4), stff::vec2(-4, 1), -8 },
            { stff::vec2(13, 8), stff::vec2(-2, -3), -50 },
        };

        for (scaffolding::vec::dot<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, length)
    {
        std::vector<scaffolding::vec::length<float, 2>> tests =
        {
            { stff::vec2(), 0 },
            { stff::vec2(1), stff::constants::sqrt_two },
            { stff::vec2(2, 2), std::sqrt(8.f) },
            { stff::vec2(3, 4), 5 },
            { stff::vec2(-3, 4), 5 },
            { stff::vec2(3, -4), 5 },
            { stff::vec2(-3, -4), 5 },
        };

        for (scaffolding::vec::length<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, normalize)
    {
        std::vector<scaffolding::vec::normalize<float, 2>> tests =
        {
            { stff::vec2(1), stff::vec2(stff::constants::sqrt_two_inv) },
            { stff::vec2(3), stff::vec2(stff::constants::sqrt_two_inv) },
            { stff::vec2(300), stff::vec2(stff::constants::sqrt_two_inv) },
            { stff::vec2(1000), stff::vec2(stff::constants::sqrt_two_inv) },
            { stff::vec2(-1), stff::vec2(-stff::constants::sqrt_two_inv) },
            { stff::vec2(-3), stff::vec2(-stff::constants::sqrt_two_inv) },
            { stff::vec2(-300), stff::vec2(-stff::constants::sqrt_two_inv) },
            { stff::vec2(-1000), stff::vec2(-stff::constants::sqrt_two_inv) },
            { stff::vec2(1, 0), stff::vec2(1, 0) },
            { stff::vec2(4, 0), stff::vec2(1, 0) },
            { stff::vec2(80, 0), stff::vec2(1, 0) },
            { stff::vec2(3, 4), stff::vec2(0.6f, 0.8f) },
            { stff::vec2(-3, 4), stff::vec2(-0.6f, 0.8f) },
            { stff::vec2(3, -4), stff::vec2(0.6f, -0.8f) },
            { stff::vec2(-3, -4), stff::vec2(-0.6f, -0.8f) },
        };

        for (scaffolding::vec::normalize<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, cast)
    {
        std::vector<scaffolding::vec::cast<float, double, 2>> tests =
        {
            { stff::vec2() },
            { stff::vec2(1.f, 2.f) },
            { stff::vec2(1.f) },
            { stff::vec2(4.f) },
        };

        for (scaffolding::vec::cast<float, double, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, equality)
    {
        std::vector<scaffolding::vec::equality<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), true },
            { stff::vec2(0), stff::vec2(0), true },
            { stff::vec2(1), stff::vec2(1), true },
            { stff::vec2(2), stff::vec2(2), true },
            { stff::vec2(), stff::vec2(1), false },
            { stff::vec2(1), stff::vec2(2), false },
            { stff::vec2(2), stff::vec2(3), false },
            { stff::vec2(3), stff::vec2(4), false },
        };

        for (scaffolding::vec::equality<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, negate)
    {
        std::vector<scaffolding::vec::negate<float, 2>> tests =
        {
            { stff::vec2() },
            { stff::vec2(1.f, 2.f) },
            { stff::vec2(1.f) },
        };

        for (scaffolding::vec::negate<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

} // stf::math