#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/interval.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

    TEST(interval, contains_point)
    {
        std::vector<scaffolding::math::interval::contains_point<float>> tests =
        {
            // closed intervals
            { stff::interval(0, 6), boundary_types::closed, 0, true },
            { stff::interval(0, 6), boundary_types::closed, 3, true },
            { stff::interval(0, 6), boundary_types::closed, 6, true },
            { stff::interval(2, 6), boundary_types::closed, 0, false },
            { stff::interval(2, 6), boundary_types::closed, 1.999999f, false },
            { stff::interval(2, 6), boundary_types::closed, 6.000001f, false },
            { stff::interval(2, 6), boundary_types::closed, 8, false },
            // open intervals
            { stff::interval(0, 6), boundary_types::open, 0, false },
            { stff::interval(0, 6), boundary_types::open, 3, true },
            { stff::interval(0, 6), boundary_types::open, 6, false },
            { stff::interval(2, 6), boundary_types::open, 0, false },
            { stff::interval(2, 6), boundary_types::open, 1.999999f, false },
            { stff::interval(2, 6), boundary_types::open, 6.000001f, false },
            { stff::interval(2, 6), boundary_types::open, 8, false },
        };
        scaffolding::verify(tests);
    }

} // stf::math