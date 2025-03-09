#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/math/scaffolding/matrix.hpp"

namespace stf::math
{

    TEST(mtx3, equality)
    {
        std::vector<scaffolding::mtx::equality<float, 3>> tests =
        {
            { stff::mtx3(), stff::mtx3(), true },
            { stff::mtx3(1), stff::mtx3(1), true },
            { stff::mtx3(1), stff::mtx3(2), false },
        };

        for (scaffolding::mtx::equality<float, 3> const& test : tests) { scaffolding::mtx::verify(test); }
    }

    TEST(mtx3, inverse)
    {
        std::vector<scaffolding::mtx::inverse<float, 3>> tests =
        {
            { stff::mtx3() },
            { stff::mtx3(stff::vec3(2)) },
            { stff::mtx3(stff::vec3(-2)) },
            // TODO (stouff) write more tests
        };

        for (scaffolding::mtx::inverse<float, 3> const& test : tests) { scaffolding::mtx::verify(test); }
    }

} // stf::math