#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "alg/scaffolding/circle.hpp"

namespace stf {
namespace alg {

    TEST(circle, conversion)
    {
        std::vector<scaffolding::circle::conversion<float>> tests = 
        {
            { 0, 0 },
            { stff::constants::quarter_pi, 45.f },
            { stff::constants::half_pi, 90.f },
            { stff::constants::pi, 180.f },
            { stff::constants::tau, 360.f },
        };

        for (scaffolding::circle::conversion<float> const& test : tests) { scaffolding::circle::verify(test); }
    };

} // math
} // stf