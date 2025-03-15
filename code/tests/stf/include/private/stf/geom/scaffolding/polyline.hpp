#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polyline.hpp>

namespace stf::geom::scaffolding::polyline
{

    template<typename T, size_t N>
    struct length
    {
        geom::polyline<T, N> polyline;
        T len;
    };

    template<typename T, size_t N>
    void verify(length<T, N> const& test)
    {
        ASSERT_EQ(test.len, test.polyline.length()) << "failed polyline.length()";
    }

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        geom::polyline<T, N> polyline;
        math::vec<T, N> point;
        T dist_squared;
    };

    template<typename T, size_t N>
    void verify(dist_and_dist_squared<T, N> const& test)
    {
        ASSERT_EQ(std::sqrt(test.dist_squared), test.polyline.dist(test.point)) << "failed to compute distance to polyline";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.polyline, test.point)) << "failed distance from polyline to vec";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.point, test.polyline)) << "failed distance from vec to polyline";
        
        ASSERT_EQ(test.dist_squared, test.polyline.dist_squared(test.point)) << "failed to compute the squared distance to polyline";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.polyline, test.point)) << "failed distance squared from polyline to vec";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.point, test.polyline)) << "failed distance squared from vec to polyline";
    }

    template<typename T, size_t N>
    struct interpolate
    {
        geom::polyline<T, N> polyline;
        T t;
        math::vec<T, N> point;
    };

    template<typename T, size_t N>
    void verify(interpolate<T, N> const& test)
    {
        ASSERT_EQ(test.point, test.polyline.interpolate(test.t)) << "failed to interpolate polyline";
    }

}