#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/alg/triangulation.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::alg
{

    TEST(triangulation, earclip_polygon)
    {
        std::vector<scaffolding::alg::triangulation::earclip_polygon<float>> tests =
        {
            { stff::polygon({ stff::vec2(0, 0), stff::vec2(1, 0), stff::vec2(0, 1) }) },
        };
        scaffolding::verify(tests);
    }

} // stf::alg