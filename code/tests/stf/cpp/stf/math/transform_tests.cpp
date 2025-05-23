#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/math/transform.hpp>

#include "stf/scaffolding/math/transform.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{
    
    TEST(transform, rotate2)
    {
        std::vector<scaffolding::math::transform::rotate2<float>> tests = 
        {
            // initial              rotation                    expected
            { stff::vec2(1, 0),     stff::constants::pi,        stff::vec2(-1, 0) },
            { stff::vec2(1, 0),     stff::constants::half_pi,   stff::vec2(0, 1) },
            { stff::vec2(1, 0),     -stff::constants::half_pi,  stff::vec2(0, -1) },
        };
        scaffolding::verify(tests);
    }

    TEST(transform, orbit2)
    {
        std::vector<scaffolding::math::transform::orbit2<float>> tests = 
        {
            // initial              focus               rotation                    expected
            { stff::vec2(1, 0),     stff::vec2(0),      stff::constants::zero,      stff::vec2(1, 0) },
            { stff::vec2(1, 1),     stff::vec2(0),      stff::constants::zero,      stff::vec2(1, 1) },
            { stff::vec2(-1, 0),     stff::vec2(0),      stff::constants::zero,      stff::vec2(-1, 0) },
            { stff::vec2(1, 0),     stff::vec2(0),      stff::constants::pi,        stff::vec2(-1, 0) },
            { stff::vec2(1, 0),     stff::vec2(0),      stff::constants::half_pi,   stff::vec2(0, 1) },
            { stff::vec2(1, 0),     stff::vec2(0),      -stff::constants::half_pi,  stff::vec2(0, -1) },
            { stff::vec2(4, 0),     stff::vec2(1, 0),   stff::constants::half_pi,   stff::vec2(1, 3) },
        };
        scaffolding::verify(tests);
    }

    TEST(transform, rotate3)
    {
        std::vector<scaffolding::math::transform::rotate3<float>> tests = 
        {
            // initial              axis                                rotation                    expected
            // idempotent rotations
            { stff::vec3(0, -1, 0), stff::vec3(0, 0, 1),                stff::constants::zero,      stff::vec3(0, -1, 0) },
            { stff::vec3(0, -1, 0), stff::vec3(0, 0, 1),                -stff::constants::zero,     stff::vec3(0, -1, 0) },
            { stff::vec3(2, 2, 2),  stff::vec3(1, 1, 1).normalized(),   stff::constants::half_pi,   stff::vec3(2, 2, 2)},
            { stff::vec3(1, 0, 0),  stff::vec3(1, 0, 1).normalized(),   stff::constants::zero,      stff::vec3(1, 0, 0) },
            { stff::vec3(1, 0, 0),  stff::vec3(1, 0, 1).normalized(),   stff::constants::two_pi,    stff::vec3(1, 0, 0) },
            // actual rotations
            { stff::vec3(1, 0, 0),  stff::vec3(0, 0, 1),                stff::constants::half_pi,   stff::vec3(0, 1, 0) },
            { stff::vec3(1, 0, 0),  stff::vec3(1, 0, 1).normalized(),   stff::constants::pi,        stff::vec3(0, 0, 1) },
        };
        scaffolding::verify(tests);
    }

    TEST(transform, orbit3)
    {
        std::vector<scaffolding::math::transform::orbit3<float>> tests = 
        {
            // initial              focus           right                   delta phi                       delta theta                 expected
            { stff::vec3(0, -1, 0), stff::vec3(),   stff::vec3(1, 0, 0),    stff::constants::zero,          stff::constants::zero,      stff::vec3(0, -1, 0) },
            { stff::vec3(0, -1, 0), stff::vec3(),   stff::vec3(1, 0, 0),    -stff::constants::quarter_pi,   stff::constants::half_pi,   stff::vec3(0.707107f, 0, 0.707107f) },
        };
        scaffolding::verify(tests);
    }

} // stf::math