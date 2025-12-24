#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/vector.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(vec2, read)
{
    std::vector<scaffolding::math::vec::read<float, 2>> tests = {
        {stff::vec2(), {0.f, 0.f}},
        {stff::vec2(1.f), {1.f, 1.f}},
        {stff::vec2(1.f, 2.f), {1.f, 2.f}},
    };
    scaffolding::verify(tests);
}

TEST(vec2, write)
{
    std::vector<scaffolding::math::vec::write<float, 2>> tests = {
        {stff::vec2(), 0, 8.f},
        {stff::vec2(1.f, 2.f), 0, 10.f},
        {stff::vec2(1.f), 1, -5.f},
    };
    scaffolding::verify(tests);
}

TEST(vec2, add)
{
    std::vector<scaffolding::math::vec::add<float, 2>> tests = {
        {stff::vec2(), stff::vec2(), stff::vec2()},
        {stff::vec2(), stff::vec2(1, 6), stff::vec2(1, 6)},
        {stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(5, 9)},
        {stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-4, -1)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, subtract)
{
    std::vector<scaffolding::math::vec::subtract<float, 2>> tests = {
        {stff::vec2(), stff::vec2(), stff::vec2()},
        {stff::vec2(), stff::vec2(1, 6), stff::vec2(-1, -6)},
        {stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(3, -3)},
        {stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-6, -5)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, scale)
{
    std::vector<scaffolding::math::vec::scale<float, 2>> tests = {
        {stff::vec2(), 0, stff::vec2()},
        {stff::vec2(), 1, stff::vec2()},
        {stff::vec2(1, -1), 1, stff::vec2(1, -1)},
        {stff::vec2(1, -1), -1, stff::vec2(-1, 1)},
        {stff::vec2(1, -1), -2, stff::vec2(-2, 2)},
        {stff::vec2(2, -3), -2, stff::vec2(-4, 6)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, divide)
{
    std::vector<scaffolding::math::vec::divide<int, 2>> tests = {
        {stfi::vec2(0, 0), 1, stfi::vec2(0, 0)},         {stfi::vec2(0, 0), 10, stfi::vec2(0, 0)},
        {stfi::vec2(100, 100), 1, stfi::vec2(100, 100)}, {stfi::vec2(100, 100), 10, stfi::vec2(10, 10)},
        {stfi::vec2(100, 100), 2, stfi::vec2(50, 50)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, dot)
{
    std::vector<scaffolding::math::vec::dot<float, 2>> tests = {
        {stff::vec2(), stff::vec2(), 0},
        {stff::vec2(1), stff::vec2(1), 2},
        {stff::vec2(1, 4), stff::vec2(4, 1), 8},
        {stff::vec2(1, -4), stff::vec2(4, 1), 0},
        {stff::vec2(1, -4), stff::vec2(-4, 1), -8},
        {stff::vec2(13, 8), stff::vec2(-2, -3), -50},
    };
    scaffolding::verify(tests);
}

TEST(vec2, length)
{
    std::vector<scaffolding::math::vec::length<float, 2>> tests = {
        {stff::vec2(), 0},
        {stff::vec2(1), stff::constants::sqrt_two},
        {stff::vec2(2, 2), std::sqrt(8.f)},
        {stff::vec2(3, 4), 5},
        {stff::vec2(-3, 4), 5},
        {stff::vec2(3, -4), 5},
        {stff::vec2(-3, -4), 5},
    };
    scaffolding::verify(tests);
}

TEST(vec2, normalize)
{
    std::vector<scaffolding::math::vec::normalize<float, 2>> tests = {
        {stff::vec2(1), stff::vec2(stff::constants::sqrt_two_inv)},
        {stff::vec2(3), stff::vec2(stff::constants::sqrt_two_inv)},
        {stff::vec2(300), stff::vec2(stff::constants::sqrt_two_inv)},
        {stff::vec2(1000), stff::vec2(stff::constants::sqrt_two_inv)},
        {stff::vec2(-1), stff::vec2(-stff::constants::sqrt_two_inv)},
        {stff::vec2(-3), stff::vec2(-stff::constants::sqrt_two_inv)},
        {stff::vec2(-300), stff::vec2(-stff::constants::sqrt_two_inv)},
        {stff::vec2(-1000), stff::vec2(-stff::constants::sqrt_two_inv)},
        {stff::vec2(1, 0), stff::vec2(1, 0)},
        {stff::vec2(4, 0), stff::vec2(1, 0)},
        {stff::vec2(80, 0), stff::vec2(1, 0)},
        {stff::vec2(3, 4), stff::vec2(0.6f, 0.8f)},
        {stff::vec2(-3, 4), stff::vec2(-0.6f, 0.8f)},
        {stff::vec2(3, -4), stff::vec2(0.6f, -0.8f)},
        {stff::vec2(-3, -4), stff::vec2(-0.6f, -0.8f)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, cast)
{
    std::vector<scaffolding::math::vec::cast<float, double, 2>> tests = {
        {stff::vec2()},
        {stff::vec2(1.f, 2.f)},
        {stff::vec2(1.f)},
        {stff::vec2(4.f)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, equality)
{
    std::vector<scaffolding::math::vec::equality<float, 2>> tests = {
        {stff::vec2(), stff::vec2(), true},    {stff::vec2(0), stff::vec2(0), true},
        {stff::vec2(1), stff::vec2(1), true},  {stff::vec2(2), stff::vec2(2), true},
        {stff::vec2(), stff::vec2(1), false},  {stff::vec2(1), stff::vec2(2), false},
        {stff::vec2(2), stff::vec2(3), false}, {stff::vec2(3), stff::vec2(4), false},
    };
    scaffolding::verify(tests);
}

TEST(vec2, negate)
{
    std::vector<scaffolding::math::vec::negate<float, 2>> tests = {
        {stff::vec2()},
        {stff::vec2(1.f, 2.f)},
        {stff::vec2(1.f)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, hadamard_multipy)
{
    std::vector<scaffolding::math::vec::hadamard_multiply<float, 2>> tests = {
        {stff::vec2(), stff::vec2(1), stff::vec2()},
        {stff::vec2(1, 0), stff::vec2(0, 1), stff::vec2()},
        {stff::vec2(1, 0), stff::vec2(1, 0), stff::vec2(1, 0)},
        {stff::vec2(0, 1), stff::vec2(0, 10), stff::vec2(0, 10)},
        {stff::vec2(2, 5), stff::vec2(3, 4), stff::vec2(6, 20)},
    };
    scaffolding::verify(tests);
}

TEST(vec2, hadamard_divide)
{
    std::vector<scaffolding::math::vec::hadamard_divide<float, 2>> tests = {
        {stff::vec2(), stff::vec2(1), stff::vec2()},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math