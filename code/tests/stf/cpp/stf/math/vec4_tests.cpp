#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/vector.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(vec4, equality)
{
    std::vector<scaffolding::math::vec::equality<float, 4>> tests = {
        {stff::vec4(), stff::vec4(), true},    {stff::vec4(0), stff::vec4(0), true},
        {stff::vec4(1), stff::vec4(1), true},  {stff::vec4(2), stff::vec4(2), true},
        {stff::vec4(), stff::vec4(1), false},  {stff::vec4(1), stff::vec4(2), false},
        {stff::vec4(2), stff::vec4(3), false}, {stff::vec4(3), stff::vec4(4), false},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math