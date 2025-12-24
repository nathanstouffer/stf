#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/intersect.hpp>

namespace stf::scaffolding::alg::intersect
{

template <typename T>
struct ray_with_plane
{
    stf::geom::ray3<T> ray;
    stf::geom::plane<T> plane;
    std::optional<stf::math::vec3<T>> expected;

    void verify(size_t const i) const
    {
        stf::geom::plane<T> flipped = stf::geom::plane<T>(plane.point(), -plane.normal());

        ASSERT_EQ(expected, stf::alg::intersect(ray, plane)) << info(i) << "Failed intersect(ray, plane)";
        ASSERT_EQ(expected, stf::alg::intersect(plane, ray)) << info(i) << "Failed intersect(plane, ray)";

        ASSERT_EQ(expected, stf::alg::intersect(ray, flipped)) << info(i) << "Failed intersect(ray, flipped)";
        ASSERT_EQ(expected, stf::alg::intersect(flipped, ray)) << info(i) << "Failed intersect(flipped, ray)";
    }
};

} // namespace stf::scaffolding::alg::intersect