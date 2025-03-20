#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/hypersphere.hpp"

namespace stf::geom
{

    TEST(sphere, encloses)
    {
        std::vector<scaffolding::hypersphere::encloses<float, 3>> tests =
        {
            { stff::sphere(stff::vec3(0), 1), stff::vec3(0), true },
            { stff::sphere(stff::vec3(0), 1), stff::vec3(1, 0, 0), true },
            { stff::sphere(stff::vec3(0), 1), stff::vec3(1), false },
            { stff::sphere(stff::vec3(10), 5), stff::vec3(0), false },
            { stff::sphere(stff::vec3(10), 5), stff::vec3(1), false },
            { stff::sphere(stff::vec3(10), 5), stff::vec3(9), true },
            { stff::sphere(stff::vec3(10), 5), stff::vec3(10), true },
            { stff::sphere(stff::vec3(10), 5), stff::vec3(11), true },
        };

        for (scaffolding::hypersphere::encloses<float, 3> const& test : tests)
        {
            scaffolding::hypersphere::verify(test);
        }
    }

} // stf::geom