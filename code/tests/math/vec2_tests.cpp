#include <vector>

#include <gtest/gtest.h>

#include <stf/types.h>

#include "scaffolding/compare.h"

namespace stf {
namespace math {

    TEST(vec2, equality)
    {
        std::vector<scaffolding::vec_equality<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), true },
            { stff::vec2(0), stff::vec2(0), true },
            { stff::vec2(1), stff::vec2(1), true },
            { stff::vec2(2), stff::vec2(2), true },
            { stff::vec2(), stff::vec2(1), false },
            { stff::vec2(1), stff::vec2(2), false },
            { stff::vec2(2), stff::vec2(3), false },
            { stff::vec2(3), stff::vec2(4), false },
        };

        for (scaffolding::vec_equality<float, 2> const& test : tests)
        {
            scaffolding::verify(test);
        }
    }

} // math
} // stf