#include <vector>

#include <gtest/gtest.h>

#include <stf/types.h>

#include "scaffolding/compare.h"

namespace stf {
namespace math {

    TEST(vec5, equality)
    {
        std::vector<scaffolding::vec_equality<float, 5>> tests =
        {
            { stff::vec<5>(), stff::vec<5>(), true },
            { stff::vec<5>(0), stff::vec<5>(0), true },
            { stff::vec<5>(1), stff::vec<5>(1), true },
            { stff::vec<5>(2), stff::vec<5>(2), true },
            { stff::vec<5>(), stff::vec<5>(1), false },
            { stff::vec<5>(1), stff::vec<5>(2), false },
            { stff::vec<5>(2), stff::vec<5>(3), false },
            { stff::vec<5>(3), stff::vec<5>(4), false },
        };

        for (scaffolding::vec_equality<float, 5> const& test : tests)
        {
            scaffolding::verify(test);
        }
    }

} // math
} // stf