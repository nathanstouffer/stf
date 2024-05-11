#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/cam/scaffolding/frustum.hpp"

namespace stf::cam
{

    TEST(frustum, intersects_fast)
    {
        std::vector<scaffolding::frustum::intersects_fast<float>> tests =
        {
            // TODO (stouff) write this test
        };

        for (scaffolding::frustum::intersects_fast<float> const& test : tests) { scaffolding::frustum::verify(test); }
    }

} // stf::cam