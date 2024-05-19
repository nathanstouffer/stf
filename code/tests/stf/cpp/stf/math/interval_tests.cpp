#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/interval.hpp"

namespace stf::math
{

    TEST(interval, contains_point)
    {
        std::vector<scaffolding::interval::contains_point<float>> tests =
        {
            // closed intervals
            { stff::interval(0, 6), boundary_types::CLOSED, 0, true },
            { stff::interval(0, 6), boundary_types::CLOSED, 3, true },
            { stff::interval(0, 6), boundary_types::CLOSED, 6, true },
            { stff::interval(2, 6), boundary_types::CLOSED, 0, false },
            { stff::interval(2, 6), boundary_types::CLOSED, 1.999999, false },
            { stff::interval(2, 6), boundary_types::CLOSED, 6.000001, false },
            { stff::interval(2, 6), boundary_types::CLOSED, 8, false },
            // open intervals
            { stff::interval(0, 6), boundary_types::OPEN, 0, false },
            { stff::interval(0, 6), boundary_types::OPEN, 3, true },
            { stff::interval(0, 6), boundary_types::OPEN, 6, false },
            { stff::interval(2, 6), boundary_types::OPEN, 0, false },
            { stff::interval(2, 6), boundary_types::OPEN, 1.999999, false },
            { stff::interval(2, 6), boundary_types::OPEN, 6.000001, false },
            { stff::interval(2, 6), boundary_types::OPEN, 8, false },
        };

        for (scaffolding::interval::contains_point<float> const& test : tests)
        {
            scaffolding::interval::verify(test);
        }
    }

} // stf::math