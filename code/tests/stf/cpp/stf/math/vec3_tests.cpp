#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/vector.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{

    TEST(vec3, equality)
    {
        std::vector<scaffolding::math::vec::equality<float, 3>> tests =
        {
            { stff::vec3(), stff::vec3(), true },
            { stff::vec3(0), stff::vec3(0), true },
            { stff::vec3(1), stff::vec3(1), true },
            { stff::vec3(2), stff::vec3(2), true },
            { stff::vec3(), stff::vec3(1), false },
            { stff::vec3(1), stff::vec3(2), false },
            { stff::vec3(2), stff::vec3(3), false },
            { stff::vec3(3), stff::vec3(4), false },
        };
        scaffolding::verify(tests);
    }

} // stf::math