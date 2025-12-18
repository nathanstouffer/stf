#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/vector.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(vec5, equality)
{
    std::vector<scaffolding::math::vec::equality<float, 5>> tests = {
        {stff::vec<5>(), stff::vec<5>(), true},
        {stff::vec<5>(0.f), stff::vec<5>(0.f), true},
        {stff::vec<5>(1.f), stff::vec<5>(1.f), true},
        {stff::vec<5>(2.f), stff::vec<5>(2.f), true},
        {stff::vec<5>(), stff::vec<5>(1.f), false},
        {stff::vec<5>(1.f), stff::vec<5>(2.f), false},
        {stff::vec<5>(2.f), stff::vec<5>(3.f), false},
        {stff::vec<5>(3.f), stff::vec<5>(4.f), false},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math