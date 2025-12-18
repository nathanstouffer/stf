#pragma once

#include <gtest/gtest.h>

#include <stf/math/constants.hpp>
#include <stf/geom/ray.hpp>

namespace stf::scaffolding::geom::ray
{

template <typename T, size_t N>
struct dist_and_dist_squared
{
    stf::geom::ray<T, N> beam;
    stf::math::vec<T, N> point;
    T dist_squared;

    void verify(size_t const i) const
    {
        ASSERT_NEAR(std::sqrt(dist_squared), beam.dist(point), stf::math::constants<T>::tol)
            << info(i) << "failed distance between ray and point";
        ASSERT_NEAR(std::sqrt(dist_squared), stf::geom::dist(beam, point),
                    stf::math::constants<T>::tol)
            << info(i) << "failed distance between ray and point";
        ASSERT_NEAR(std::sqrt(dist_squared), stf::geom::dist(point, beam),
                    stf::math::constants<T>::tol)
            << info(i) << "failed distance between point and ray";
        ASSERT_NEAR(dist_squared, beam.dist_squared(point), stf::math::constants<T>::tol)
            << info(i) << "failed distance squared from ray to vec";
        ASSERT_NEAR(dist_squared, stf::geom::dist_squared(beam, point),
                    stf::math::constants<T>::tol)
            << info(i) << "failed distance squared from ray to vec";
        ASSERT_NEAR(dist_squared, stf::geom::dist_squared(point, beam),
                    stf::math::constants<T>::tol)
            << info(i) << "failed distance squared from vec to ray";
    }
};

} // namespace stf::scaffolding::geom::ray