#pragma once

#include <gtest/gtest.h>

#include <stf/geom/segment.hpp>

namespace stf::scaffolding::geom::segment
{

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        stf::geom::segment<T, N> seg;
        stf::math::vec<T, N> point;
        T dist_squared;

        void verify(size_t const i) const
        {
            ASSERT_EQ(std::sqrt(dist_squared),seg.dist(point)) << info(i) << "failed distance between segment and point";
            ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(seg, point)) << info(i) << "failed distance between segment and point";
            ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(point, seg)) << info(i) << "failed distance between point and segment";
            ASSERT_EQ(dist_squared, seg.dist_squared(point)) << info(i) << "failed distance squared from segment to vec";
            ASSERT_EQ(dist_squared, stf::geom::dist_squared(seg, point)) << info(i) << "failed distance squared from segment to vec";
            ASSERT_EQ(dist_squared, stf::geom::dist_squared(point, seg)) << info(i) << "failed distance squared from vec to segment";
        }
    };

    template<typename T, size_t N>
    struct interpolate
    {
        stf::geom::segment<T, N> seg;
        T t;
        stf::math::vec<T, N> point;

        void verify(size_t const i) const
        {
            ASSERT_EQ(point, seg.interpolate(t)) << info(i) << "failed interpolation test";
        }
    };

} // stf::scaffolding::geom::segment