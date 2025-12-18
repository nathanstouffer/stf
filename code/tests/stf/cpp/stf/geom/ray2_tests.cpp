#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/geom/ray.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::geom
{

    TEST(ray2, dist_and_dist_squared)
    {
        std::vector<scaffolding::geom::ray::dist_and_dist_squared<float, 2>> tests =
        {
            { stff::ray2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(0), 0 },
            { stff::ray2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(4, 0), 0 },
            { stff::ray2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(-2, 0), 4 },
            { stff::ray2(stff::vec2(0), stff::vec2(1, 0)), stff::vec2(2), 4 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(0), 0 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(1), 0 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(5), 0 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(-2), 8 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(1, 0), 0.5 },
            { stff::ray2(stff::vec2(0), stff::vec2(1)), stff::vec2(0, -1), 1 },
        };
        scaffolding::verify(tests);
    }

} // stf::geom