#pragma once

#include <gtest/gtest.h>

#include <stf/math/constants.hpp>
#include <stf/geom/ray.hpp>

namespace stf::geom::scaffolding::ray
{

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        geom::ray<T, N> const beam;
        math::vec<T, N> const point;
        T const dist_squared;
    };

    template<typename T, size_t N>
    void verify(dist_and_dist_squared<T, N> const& test)
    {
        ASSERT_NEAR(std::sqrt(test.dist_squared), test.beam.dist(test.point), math::constants<T>::tol) << "failed distance between ray and point";
        ASSERT_NEAR(std::sqrt(test.dist_squared), geom::dist(test.beam, test.point), math::constants<T>::tol) << "failed distance between ray and point";
        ASSERT_NEAR(std::sqrt(test.dist_squared), geom::dist(test.point, test.beam), math::constants<T>::tol) << "failed distance between point and ray";
        ASSERT_NEAR(test.dist_squared, test.beam.dist_squared(test.point), math::constants<T>::tol) << "failed distance squared from ray to vec";
        ASSERT_NEAR(test.dist_squared, geom::dist_squared(test.beam, test.point), math::constants<T>::tol) << "failed distance squared from ray to vec";
        ASSERT_NEAR(test.dist_squared, geom::dist_squared(test.point, test.beam), math::constants<T>::tol) << "failed distance squared from vec to ray";
    }

} // stf::geom::scaffolding::ray