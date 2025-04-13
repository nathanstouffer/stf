#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/cinterval.hpp"

namespace stf::math
{

    TEST(cinterval, contains_point)
    {
        std::vector<scaffolding::cinterval::contains_point<float>> tests =
        {
            // closed cintervals
            { stff::cinterval(0, 6), boundary_types::CLOSED, 0, true },
            { stff::cinterval(0, 6), boundary_types::CLOSED, 3, true },
            { stff::cinterval(0, 6), boundary_types::CLOSED, 6, true },
            { stff::cinterval(2, 6), boundary_types::CLOSED, 0, false },
            { stff::cinterval(2, 6), boundary_types::CLOSED, 1.999999f, false },
            { stff::cinterval(2, 6), boundary_types::CLOSED, 6.000001f, false },
            { stff::cinterval(2, 6), boundary_types::CLOSED, 8, false },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 5, true },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 6, true },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 0, true },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 1, true },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 2, true },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 4, false },
            { stff::cinterval(5, 2), boundary_types::CLOSED, 3, false },
            // open cintervals
            { stff::cinterval(0, 6), boundary_types::OPEN, 0, false },
            { stff::cinterval(0, 6), boundary_types::OPEN, 3, true },
            { stff::cinterval(0, 6), boundary_types::OPEN, 6, false },
            { stff::cinterval(2, 6), boundary_types::OPEN, 0, false },
            { stff::cinterval(2, 6), boundary_types::OPEN, 1.999999f, false },
            { stff::cinterval(2, 6), boundary_types::OPEN, 6.000001f, false },
            { stff::cinterval(2, 6), boundary_types::OPEN, 8, false },
            { stff::cinterval(5, 2), boundary_types::OPEN, 6, true },
            { stff::cinterval(5, 2), boundary_types::OPEN, 0, true },
            { stff::cinterval(5, 2), boundary_types::OPEN, 1, true },
            { stff::cinterval(5, 2), boundary_types::OPEN, 5, false },
            { stff::cinterval(5, 2), boundary_types::OPEN, 2, false },
            { stff::cinterval(5, 2), boundary_types::OPEN, 4, false },
            { stff::cinterval(5, 2), boundary_types::OPEN, 3, false },
        };

        for (scaffolding::cinterval::contains_point<float> const& test : tests)
        {
            scaffolding::cinterval::verify(test);
        }
    }

} // stf::math