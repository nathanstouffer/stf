#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/sphere.hpp"

namespace stf::geom
{

    TEST(sphere3, encloses)
    {
        std::vector<scaffolding::sphere::encloses<float, 3>> tests =
        {
            { stff::sphere3(stff::vec3(0), 1), stff::vec3(0), true },
            { stff::sphere3(stff::vec3(0), 1), stff::vec3(1, 0, 0), true },
            { stff::sphere3(stff::vec3(0), 1), stff::vec3(1), false },
            { stff::sphere3(stff::vec3(10), 5), stff::vec3(0), false },
            { stff::sphere3(stff::vec3(10), 5), stff::vec3(1), false },
            { stff::sphere3(stff::vec3(10), 5), stff::vec3(9), true },
            { stff::sphere3(stff::vec3(10), 5), stff::vec3(10), true },
            { stff::sphere3(stff::vec3(10), 5), stff::vec3(11), true },
        };

        for (scaffolding::sphere::encloses<float, 3> const& test : tests)
        {
            scaffolding::sphere::verify(test);
        }
    }

} // stf::geom