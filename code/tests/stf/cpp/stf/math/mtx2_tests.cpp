#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/matrix.hpp"

namespace stf::math
{

    TEST(mtx2, equality)
    {
        std::vector<scaffolding::mtx::equality<float, 2>> tests =
        {
            { stff::mtx2(), stff::mtx2(), true },
            { stff::mtx2(1), stff::mtx2(1), true },
            { stff::mtx2(1), stff::mtx2(2), false },
        };

        for (scaffolding::mtx::equality<float, 2> const& test : tests) { scaffolding::mtx::verify(test); }
    }

} // stf::math