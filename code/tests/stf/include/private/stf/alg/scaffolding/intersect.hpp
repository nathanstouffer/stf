#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/intersect.hpp>

namespace stf::alg::scaffolding::intersect
{

    template<typename T>
    struct ray_with_plane
    {
        geom::ray3<T> ray;
        geom::plane<T> plane;
        std::optional<math::vec3<T>> expected;
    };

    template<typename T>
    void verify(ray_with_plane<T> const& test)
    {
        geom::plane<T> flipped = geom::plane<T>(test.plane.point(), -test.plane.normal());

        ASSERT_EQ(test.expected, alg::intersect(test.ray, test.plane)) << "Failed intersect(ray, plane)";
        ASSERT_EQ(test.expected, alg::intersect(test.plane, test.ray)) << "Failed intersect(plane, ray)";
        
        ASSERT_EQ(test.expected, alg::intersect(test.ray, flipped)) << "Failed intersect(ray, flipped)";
        ASSERT_EQ(test.expected, alg::intersect(flipped, test.ray)) << "Failed intersect(flipped, ray)";
    }

} // stf::alg::scaffolding::intersect