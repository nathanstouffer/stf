#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/transform.hpp>

#include "stf/alg/scaffolding/transform.hpp"

namespace stf {
namespace alg {

    TEST(transform, rotate3)
    {
        std::vector<scaffolding::transform::rotate3<float>> tests = 
        {
            { stff::vec3(1, 0, 0), stff::vec3(0, 0, 1), stff::constants::half_pi, stff::vec3(0, 1, 0) },
        };

        for (scaffolding::transform::rotate3<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

    TEST(transform, orbit3)
    {
        std::vector<scaffolding::transform::orbit3<float>> tests = 
        {
            { stff::vec3(0, -1, 0), stff::vec3(), stff::vec3(1, 0, 0), -stff::constants::quarter_pi, stff::constants::half_pi, stff::vec3(0.707107, 0, 0.707107) },
        };

        for (scaffolding::transform::orbit3<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

} // math
} // stf