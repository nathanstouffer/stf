#include <vector>

#include <gtest/gtest.h>

#include <stf/spatial/interval_tree.hpp>

#include "stf/spatial/scaffolding/interval_tree.hpp"

namespace stf::spatial
{

    TEST(interval_tree, something)
    {
        std::vector<scaffolding::interval_tree::something<float>> tests =
        {
            
        };

        for (scaffolding::interval_tree::something<float> const& test : tests) { scaffolding::interval_tree::verify(test); }
    }

} // stf::spatial