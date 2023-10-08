#include <vector>

#include <gtest/gtest.h>

#include <stf/types.h>

#include "scaffolding/compare.h"

namespace stf {
namespace math {

    TEST(vec3, equality)
    {
        std::vector<scaffolding::vec_equality<float, 3>> tests =
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

        for (scaffolding::vec_equality<float, 3> const& test : tests)
        {
            scaffolding::verify(test);
        }
    }

} // math
} // stf