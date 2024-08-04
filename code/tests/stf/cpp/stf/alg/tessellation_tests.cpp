#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/tessellation.hpp"

namespace stf::alg
{

    TEST(tessellation, max_segment_length)
    {
        std::vector<scaffolding::tessellation::max_segment_length<float>> tests =
        {
            { stff::polyline2({}), 0.f, {} },
        };
        
        for (scaffolding::tessellation::max_segment_length<float> const& test : tests)
        {
            scaffolding::tessellation::verify(test);
        }
    }

} // stf::alg