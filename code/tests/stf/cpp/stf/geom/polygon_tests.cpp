#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/polygon.hpp"

namespace stf::geom
{

    TEST(polygon, something)
    {
        std::vector<scaffolding::polygon::something<float>> tests =
        {

        };

        for (scaffolding::polygon::something<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

} // stf::geom