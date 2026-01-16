#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/geom/hypersphere.hpp"

namespace stf::geom
{

TEST(hypersphere3, encloses)
{
    std::vector<scaffolding::geom::hypersphere::encloses<float, 3>> tests = {
        {stff::sphere(stff::vec3(0), 1), stff::vec3(0), true},
        {stff::sphere(stff::vec3(0), 1), stff::vec3(1, 0, 0), true},
        {stff::sphere(stff::vec3(0), 1), stff::vec3(1), false},
        {stff::sphere(stff::vec3(10), 5), stff::vec3(0), false},
        {stff::sphere(stff::vec3(10), 5), stff::vec3(1), false},
        {stff::sphere(stff::vec3(10), 5), stff::vec3(9), true},
        {stff::sphere(stff::vec3(10), 5), stff::vec3(10), true},
        {stff::sphere(stff::vec3(10), 5), stff::vec3(11), true},
    };
    scaffolding::verify(tests);
}

} // namespace stf::geom