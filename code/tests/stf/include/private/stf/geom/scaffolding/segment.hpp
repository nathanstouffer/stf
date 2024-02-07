#pragma once

#include <gtest/gtest.h>

#include <stf/geom/segment.hpp>

namespace stf::geom::scaffolding::segment
{

    template<typename T, size_t N>
    struct distance_to
    {
        geom::segment<T, N> const seg;
        math::vec<T, N> const point;
        T const dist;
    };

    template<typename T, size_t N>
    void verify(distance_to<T, N> const& test)
    {
        ASSERT_EQ(test.dist, test.seg.distance_to(test.point)) << "failed distance_to test";
    }

    template<typename T, size_t N>
    struct interpolate
    {
        geom::segment<T, N> const seg;
        T const t;
        math::vec<T, N> const point;
    };

    template<typename T, size_t N>
    void verify(interpolate<T, N> const& test)
    {
        ASSERT_EQ(test.point, test.seg.interpolate(test.t)) << "failed interpolation test";
    }

} // stf::geom::scaffolding::segment