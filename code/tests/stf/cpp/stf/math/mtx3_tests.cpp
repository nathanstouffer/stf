#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/matrix.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(mtx3, equality)
{
    std::vector<scaffolding::math::mtx::equality<float, 3>> tests = {
        {stff::mtx3(), stff::mtx3(), true},
        {stff::mtx3(1), stff::mtx3(1), true},
        {stff::mtx3(1), stff::mtx3(2), false},
    };
    scaffolding::verify(tests);
}

TEST(mtx3, determinant)
{
    std::vector<scaffolding::math::mtx::determinant<float, 3>> tests = {
        {stff::mtx3(), 1},
        {stff::mtx3(stff::vec3(2)), 8},
        {stff::mtx3(stff::vec3(-2)), -8},
        {stff::mtx3(stff::vec3(-2, 2, 2)), -8},
        {stff::mtx3(stff::vec<9>(2)), 0},
        {stff::mtx3(stff::vec<9>({2, 1, 0, -3, 5, 1, 1, -1, -2})), -23},
    };
    scaffolding::verify(tests);
}

TEST(mtx3, inverted)
{
    std::vector<scaffolding::math::mtx::inverted<float, 3>> tests = {
        {stff::mtx3()},
        {stff::mtx3(stff::vec3(2))},
        {stff::mtx3(stff::vec3(-2))},
        {stf::math::rotate(stff::vec3(1), stff::constants::quarter_pi).prefix()},
        {(stf::math::rotate(stff::vec3(1), stff::constants::quarter_pi) * stf::math::scale(stff::vec3(1, 3, 2)))
             .prefix()},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math