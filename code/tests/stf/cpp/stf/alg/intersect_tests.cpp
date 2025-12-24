#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/alg/intersect.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::alg
{

TEST(intersect, ray_with_plane)
{
    std::vector<scaffolding::alg::intersect::ray_with_plane<float>> tests = {
        //// ray that is a subset of plane
        {stff::ray3(stff::vec3(), stff::vec3(1, 0, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)), stff::vec3()},
        {stff::ray3(stff::vec3(), stff::vec3(1, 1, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)), stff::vec3()},
        {stff::ray3(stff::vec3(), stff::vec3(0, 0, 1)), stff::plane(stff::vec3(), stff::vec3(1, 0, 0)), stff::vec3()},
        // ray that is parallel to plane
        {stff::ray3(stff::vec3(0, 0, 1), stff::vec3(1, 0, 0)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)),
         std::nullopt},
        {stff::ray3(stff::vec3(-1, 0, 0), stff::vec3(0, 0, 1)), stff::plane(stff::vec3(), stff::vec3(1, 0, 0)),
         std::nullopt},
        // ray is pointing towards plane
        {stff::ray3(stff::vec3(0, 0, 10), stff::vec3(1, 1, -1)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)),
         stff::vec3(10, 10, 0)},
        {stff::ray3(stff::vec3(0, 0, 100), stff::vec3(0, 0, -1)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)),
         stff::vec3()},
        // ray is pointing away from plane
        {stff::ray3(stff::vec3(0, 0, 10), stff::vec3(1, 1, 1)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)),
         std::nullopt},
        {stff::ray3(stff::vec3(0, 0, 100), stff::vec3(0, 0, 1)), stff::plane(stff::vec3(), stff::vec3(0, 0, 1)),
         std::nullopt},
    };
    scaffolding::verify(tests);
}

} // namespace stf::alg