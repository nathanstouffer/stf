#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/math/scaffolding/vector.hpp"

namespace stf::math
{

    TEST(vec4, equality)
    {
        std::vector<scaffolding::vec::equality<float, 4>> tests =
        {
            { stff::vec4(), stff::vec4(), true },
            { stff::vec4(0), stff::vec4(0), true },
            { stff::vec4(1), stff::vec4(1), true },
            { stff::vec4(2), stff::vec4(2), true },
            { stff::vec4(), stff::vec4(1), false },
            { stff::vec4(1), stff::vec4(2), false },
            { stff::vec4(2), stff::vec4(3), false },
            { stff::vec4(3), stff::vec4(4), false },
        };

        for (scaffolding::vec::equality<float, 4> const& test : tests)
        {
            scaffolding::vec::verify(test);
        }
    }

} // stf::math