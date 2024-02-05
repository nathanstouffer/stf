#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/math/scaffolding/crange.hpp"

namespace stf::math
{

    TEST(crange, contains_point)
    {
        std::vector<scaffolding::crange::contains_point<float>> tests =
        {
            // closed cranges
            { stff::crange(0, 6), stf::endpoints::CLOSED, 0, true },
            { stff::crange(0, 6), stf::endpoints::CLOSED, 3, true },
            { stff::crange(0, 6), stf::endpoints::CLOSED, 6, true },
            { stff::crange(2, 6), stf::endpoints::CLOSED, 0, false },
            { stff::crange(2, 6), stf::endpoints::CLOSED, 1.999999, false },
            { stff::crange(2, 6), stf::endpoints::CLOSED, 6.000001, false },
            { stff::crange(2, 6), stf::endpoints::CLOSED, 8, false },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 5, true },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 6, true },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 0, true },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 1, true },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 2, true },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 4, false },
            { stff::crange(5, 2), stf::endpoints::CLOSED, 3, false },
            // open cranges
            { stff::crange(0, 6), stf::endpoints::OPEN, 0, false },
            { stff::crange(0, 6), stf::endpoints::OPEN, 3, true },
            { stff::crange(0, 6), stf::endpoints::OPEN, 6, false },
            { stff::crange(2, 6), stf::endpoints::OPEN, 0, false },
            { stff::crange(2, 6), stf::endpoints::OPEN, 1.999999, false },
            { stff::crange(2, 6), stf::endpoints::OPEN, 6.000001, false },
            { stff::crange(2, 6), stf::endpoints::OPEN, 8, false },
            { stff::crange(5, 2), stf::endpoints::OPEN, 6, true },
            { stff::crange(5, 2), stf::endpoints::OPEN, 0, true },
            { stff::crange(5, 2), stf::endpoints::OPEN, 1, true },
            { stff::crange(5, 2), stf::endpoints::OPEN, 5, false },
            { stff::crange(5, 2), stf::endpoints::OPEN, 2, false },
            { stff::crange(5, 2), stf::endpoints::OPEN, 4, false },
            { stff::crange(5, 2), stf::endpoints::OPEN, 3, false },

        };

        for (scaffolding::crange::contains_point<float> const& test : tests)
        {
            scaffolding::crange::verify(test);
        }
    }

} // stf::math