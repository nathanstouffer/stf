#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/tessellation.hpp"

namespace stf::alg
{

    TEST(tessellation, polyline_via_length)
    {
        std::vector<scaffolding::tessellation::polyline_via_length<float>> tests =
        {
            { stff::polyline2(std::vector<stff::vec2>{}), 0.f, false, {} },
            { stff::polyline2(std::vector<stff::vec2>{}), 1.f, false, {} },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1,0) }), 1.f, false, { stff::vec2(0), stff::vec2(1,0) } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1,0) }), 0.5f, false, { stff::vec2(0), stff::vec2(0.5,0), stff::vec2(1,0) } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(0.8,0) }), 0.5f, false, { stff::vec2(0), stff::vec2(0.4,0), stff::vec2(0.8,0) } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(0.9,0) }), 0.3f, false, { stff::vec2(0), stff::vec2(0.3,0), stff::vec2(0.6,0), stff::vec2(0.9,0) } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1,0), stff::vec2(2,1), stff::vec2(3,0), stff::vec2(4,0) }), 1.f, false, { stff::vec2(0), stff::vec2(1,0), stff::vec2(1.5,0.5), stff::vec2(2,1), stff::vec2(2.5,0.5), stff::vec2(3,0), stff::vec2(4,0) } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1,0), stff::vec2(1) }), 1.f, false, { stff::vec2(0), stff::vec2(1,0), stff::vec2(1), } },
            { stff::polyline2({ stff::vec2(0), stff::vec2(1,0), stff::vec2(1) }), 1.f, true, { stff::vec2(0), stff::vec2(1,0), stff::vec2(1), stff::vec2(0.5) }},
        };
        
        for (scaffolding::tessellation::polyline_via_length<float> const& test : tests)
        {
            scaffolding::tessellation::verify(test);
        }
    }

} // stf::alg