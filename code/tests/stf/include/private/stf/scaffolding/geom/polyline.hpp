#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polyline.hpp>

namespace stf::scaffolding::geom::polyline
{

    template<typename T, size_t N>
    struct length
    {
        stf::geom::polyline<T, N> polyline;
        T len;

        void verify(size_t const i) const
        {
            ASSERT_EQ(len, polyline.length()) << info(i) << "failed polyline.length()";
        }
    };

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        stf::geom::polyline<T, N> polyline;
        stf::math::vec<T, N> point;
        T dist_squared;

        void verify(size_t const i) const
        {
            ASSERT_EQ(std::sqrt(dist_squared), polyline.dist(point)) << info(i) << "failed to compute distance to polyline";
            ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(polyline, point)) << info(i) << "failed distance from polyline to vec";
            ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(point, polyline)) << info(i) << "failed distance from vec to polyline";
        
            ASSERT_EQ(dist_squared, polyline.dist_squared(point)) << info(i) << "failed to compute the squared distance to polyline";
            ASSERT_EQ(dist_squared, stf::geom::dist_squared(polyline, point)) << info(i) << "failed distance squared from polyline to vec";
            ASSERT_EQ(dist_squared, stf::geom::dist_squared(point, polyline)) << info(i) << "failed distance squared from vec to polyline";
        }
    };

    template<typename T, size_t N>
    struct interpolate
    {
        stf::geom::polyline<T, N> polyline;
        T t;
        stf::math::vec<T, N> point;

        void verify(size_t const i) const
        {
            ASSERT_EQ(point, polyline.interpolate(t)) << info(i) << "failed to interpolate polyline";
        }
    };

}