#pragma once

#include <gtest/gtest.h>

#include <stf/geom/segment.hpp>

namespace stf::geom::scaffolding::segment
{

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        geom::segment<T, N> const seg;
        math::vec<T, N> const point;
        T const dist_squared;
    };

    template<typename T, size_t N>
    void verify(dist_and_dist_squared<T, N> const& test)
    {
        ASSERT_EQ(std::sqrt(test.dist_squared),test.seg.dist(test.point)) << "failed distance between segment and point";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.seg, test.point)) << "failed distance between segment and point";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.point, test.seg)) << "failed distance between point and segment";
        ASSERT_EQ(test.dist_squared, test.seg.dist_squared(test.point)) << "failed distance squared from segment to vec";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.seg, test.point)) << "failed distance squared from segment to vec";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.point, test.seg)) << "failed distance squared from vec to segment";
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