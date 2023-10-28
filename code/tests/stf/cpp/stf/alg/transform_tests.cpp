#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/transform.hpp>

#include "stf/alg/scaffolding/transform.hpp"

namespace stf {
namespace alg {

    TEST(transform, rotate2)
    {
        std::vector<scaffolding::transform::rotate2<float>> tests = 
        {
            // initial              rotation                    expected
            { stff::vec2(1, 0),     stff::constants::pi,        stff::vec2(-1, 0) },
            { stff::vec2(1, 0),     stff::constants::half_pi,   stff::vec2(0, 1) },
            { stff::vec2(1, 0),     -stff::constants::half_pi,  stff::vec2(0, -1) },
        };

        for (scaffolding::transform::rotate2<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

    TEST(transform, orbit2)
    {
        std::vector<scaffolding::transform::orbit2<float>> tests = 
        {
            // initial              focus               rotation                    expected
            { stff::vec2(1, 0),     stff::vec2(0),      stff::constants::pi,        stff::vec2(-1, 0) },
            { stff::vec2(1, 0),     stff::vec2(0),      stff::constants::half_pi,   stff::vec2(0, 1) },
            { stff::vec2(1, 0),     stff::vec2(0),      -stff::constants::half_pi,  stff::vec2(0, -1) },
            { stff::vec2(4, 0),     stff::vec2(1, 0),   stff::constants::half_pi,   stff::vec2(1, 3) },
        };

        for (scaffolding::transform::orbit2<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

    TEST(transform, rotate3)
    {
        std::vector<scaffolding::transform::rotate3<float>> tests = 
        {
            // initial              axis                    rotation                    expected
            { stff::vec3(1, 0, 0),  stff::vec3(0, 0, 1),    stff::constants::half_pi,   stff::vec3(0, 1, 0) },
        };

        for (scaffolding::transform::rotate3<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

    TEST(transform, orbit3)
    {
        std::vector<scaffolding::transform::orbit3<float>> tests = 
        {
            // initial              focus           right                   delta phi                       delta theta                 expected
            { stff::vec3(0, -1, 0), stff::vec3(),   stff::vec3(1, 0, 0),    -stff::constants::quarter_pi,   stff::constants::half_pi,   stff::vec3(0.707107, 0, 0.707107) },
        };

        for (scaffolding::transform::orbit3<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

    TEST(transform, orbit_scamera)
    {
        float constexpr half_pi = stff::constants::half_pi;
        float constexpr pi = stff::constants::pi;

        std::vector<scaffolding::transform::orbit_scamera<float>> tests = 
        {
            // initial                                          focus           delta phi                   delta theta             expected
            { stff::scamera(stff::vec3(0, 0, 10), half_pi, pi), stff::vec3(0),  -stff::constants::half_pi,  stff::constants::pi,    stff::scamera(stff::vec3(0, 10, 0), pi + half_pi, half_pi) },
        };

        for (scaffolding::transform::orbit_scamera<float> const& test : tests) { scaffolding::transform::verify(test); }
    }

} // math
} // stf