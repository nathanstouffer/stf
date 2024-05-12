#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/statistics.hpp"

namespace stf::alg
{

    TEST(statistics, median)
    {
        std::vector<scaffolding::statistics::median<float>> tests =
        {
            { { 0.f }, 0.f  },
        };

        for (scaffolding::statistics::median<float> const& test : tests)
        {
            scaffolding::statistics::verify(test);
        }
    }

} // stf::alg