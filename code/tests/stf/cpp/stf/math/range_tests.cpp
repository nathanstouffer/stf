#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/range.hpp"

namespace stf::math
{

    TEST(range, contains_point)
    {
        std::vector<scaffolding::range::contains_point<float>> tests =
        {
            // closed ranges
            { stff::range(0, 6), boundary_types::CLOSED, 0, true },
            { stff::range(0, 6), boundary_types::CLOSED, 3, true },
            { stff::range(0, 6), boundary_types::CLOSED, 6, true },
            { stff::range(2, 6), boundary_types::CLOSED, 0, false },
            { stff::range(2, 6), boundary_types::CLOSED, 1.999999, false },
            { stff::range(2, 6), boundary_types::CLOSED, 6.000001, false },
            { stff::range(2, 6), boundary_types::CLOSED, 8, false },
            // open ranges
            { stff::range(0, 6), boundary_types::OPEN, 0, false },
            { stff::range(0, 6), boundary_types::OPEN, 3, true },
            { stff::range(0, 6), boundary_types::OPEN, 6, false },
            { stff::range(2, 6), boundary_types::OPEN, 0, false },
            { stff::range(2, 6), boundary_types::OPEN, 1.999999, false },
            { stff::range(2, 6), boundary_types::OPEN, 6.000001, false },
            { stff::range(2, 6), boundary_types::OPEN, 8, false },
        };

        for (scaffolding::range::contains_point<float> const& test : tests)
        {
            scaffolding::range::verify(test);
        }
    }

} // stf::math