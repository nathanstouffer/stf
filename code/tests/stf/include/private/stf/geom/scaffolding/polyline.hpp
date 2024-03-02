#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polyline.hpp>

namespace stf::geom::scaffolding::polyline
{

    template<typename T, size_t N>
    struct length
    {
        geom::polyline<T, N> const polyline;
        T const len;
    };

    template<typename T, size_t N>
    void verify(length<T, N> const& test)
    {
        ASSERT_EQ(test.len, test.polyline.length()) << "failed polyline.length()";
    }

    template<typename T, size_t N>
    struct distance_to
    {
        geom::polyline<T, N> const polyline;
        math::vec<T, N> const point;
        T const dist;
    };

    template<typename T, size_t N>
    void verify(distance_to<T, N> const& test)
    {
        ASSERT_EQ(test.dist, test.polyline.distance_to(test.point)) << "failed to compute distance to polyline";
    }

}