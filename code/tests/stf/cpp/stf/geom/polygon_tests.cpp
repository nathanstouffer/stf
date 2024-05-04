#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/polygon.hpp"

namespace stf::geom
{
    
    TEST(polygon, is_convex)
    {
        std::vector<scaffolding::polygon::is_convex<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(2, -2) }), false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(3, 0), stff::vec2(4, 4) }), false},
        };

        for (scaffolding::polygon::is_convex<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

} // stf::geom