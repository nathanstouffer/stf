#pragma once

#include <gtest/gtest.h>

#include <stf/geom/segment.hpp>

namespace stf::geom::scaffolding::segment
{

    template<typename T, size_t N>
    struct distance
    {
        geom::segment<T, N> const seg;
        math::vec<T, N> const point;
        T const dist;
    };

    template<typename T, size_t N>
    void verify(distance<T, N> const& test)
    {
        ASSERT_EQ(test.dist, geom::dist(test.seg, test.point)) << "failed distance between segment and point";
        ASSERT_EQ(test.dist, geom::dist(test.point, test.seg)) << "failed distance between point and segment";
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