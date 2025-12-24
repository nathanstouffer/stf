#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/cinterval.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

TEST(cinterval, contains_point)
{
    std::vector<scaffolding::math::cinterval::contains_point<float>> tests = {
        // closed cintervals
        {stff::cinterval(0, 6), boundary_types::closed, 0, true},
        {stff::cinterval(0, 6), boundary_types::closed, 3, true},
        {stff::cinterval(0, 6), boundary_types::closed, 6, true},
        {stff::cinterval(2, 6), boundary_types::closed, 0, false},
        {stff::cinterval(2, 6), boundary_types::closed, 1.999999f, false},
        {stff::cinterval(2, 6), boundary_types::closed, 6.000001f, false},
        {stff::cinterval(2, 6), boundary_types::closed, 8, false},
        {stff::cinterval(5, 2), boundary_types::closed, 5, true},
        {stff::cinterval(5, 2), boundary_types::closed, 6, true},
        {stff::cinterval(5, 2), boundary_types::closed, 0, true},
        {stff::cinterval(5, 2), boundary_types::closed, 1, true},
        {stff::cinterval(5, 2), boundary_types::closed, 2, true},
        {stff::cinterval(5, 2), boundary_types::closed, 4, false},
        {stff::cinterval(5, 2), boundary_types::closed, 3, false},
        // open cintervals
        {stff::cinterval(0, 6), boundary_types::open, 0, false},
        {stff::cinterval(0, 6), boundary_types::open, 3, true},
        {stff::cinterval(0, 6), boundary_types::open, 6, false},
        {stff::cinterval(2, 6), boundary_types::open, 0, false},
        {stff::cinterval(2, 6), boundary_types::open, 1.999999f, false},
        {stff::cinterval(2, 6), boundary_types::open, 6.000001f, false},
        {stff::cinterval(2, 6), boundary_types::open, 8, false},
        {stff::cinterval(5, 2), boundary_types::open, 6, true},
        {stff::cinterval(5, 2), boundary_types::open, 0, true},
        {stff::cinterval(5, 2), boundary_types::open, 1, true},
        {stff::cinterval(5, 2), boundary_types::open, 5, false},
        {stff::cinterval(5, 2), boundary_types::open, 2, false},
        {stff::cinterval(5, 2), boundary_types::open, 4, false},
        {stff::cinterval(5, 2), boundary_types::open, 3, false},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math