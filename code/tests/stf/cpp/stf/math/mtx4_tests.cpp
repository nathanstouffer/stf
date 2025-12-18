#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/matrix.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(mtx4, equality)
{
    std::vector<scaffolding::math::mtx::equality<float, 4>> tests = {
        {stff::mtx4(), stff::mtx4(), true},
        {stff::mtx4(1), stff::mtx4(1), true},
        {stff::mtx4(1), stff::mtx4(2), false},
        {stff::mtx4(),
         stff::mtx4(stff::vec<16>({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1.1f})), false},
    };
    scaffolding::verify(tests);
}

TEST(mtx4, determinant)
{
    std::vector<scaffolding::math::mtx::determinant<float, 4>> tests = {
        {stff::mtx4(), 1},
        {stff::mtx4(stff::vec4(2)), 16},
        {stff::mtx4(stff::vec4(-2)), 16},
        {stff::mtx4(stff::vec4(-2, 2, 2, 2)), -16},
        {stff::mtx4(stff::vec<16>(2)), 0},
        {stff::mtx4(stff::vec<16>({2, 1, 0, 0, -3, 5, 1, -1, 1, -1, -2, 2, -3, 2, -1, -1})), 46},
    };
    scaffolding::verify(tests);
}

TEST(mtx4, inverted)
{
    std::vector<scaffolding::math::mtx::inverted<float, 4>> tests = {
        {stff::mtx4()},
        {stff::mtx4(stff::vec4(2))},
        {stff::mtx4(stff::vec4(-2))},
        {stf::math::rotate(stff::vec3(1), stff::constants::quarter_pi)},
        {stf::math::rotate(stff::vec3(1), stff::constants::quarter_pi) *
         stf::math::scale(stff::vec3(1, 3, 2))},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math