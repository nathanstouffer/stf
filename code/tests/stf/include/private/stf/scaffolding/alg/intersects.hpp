#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/intersects.hpp>

namespace stf::scaffolding::alg::intersects
{

    template<typename T>
    struct segment_with_segment
    {
        stf::geom::segment2<T> lhs;
        stf::geom::segment2<T> rhs;
        bool expected;

        void verify(size_t const i) const
        {
            stf::geom::segment2<T> reverse_lhs(lhs.b, lhs.a);
            stf::geom::segment2<T> reverse_rhs(rhs.b, rhs.a);

            ASSERT_EQ(expected, stf::alg::intersects(lhs, rhs)) << info(i) << "Failed intersects(lhs, rhs)";
            ASSERT_EQ(expected, stf::alg::intersects(rhs, lhs)) << info(i) << "Failed intersects(rhs, lhs)";

            ASSERT_EQ(expected, stf::alg::intersects(reverse_lhs, rhs)) << info(i) << "Failed intersects(reverse_lhs, rhs)";
            ASSERT_EQ(expected, stf::alg::intersects(rhs, reverse_lhs)) << info(i) << "Failed intersects(rhs, reverse_lhs)";

            ASSERT_EQ(expected, stf::alg::intersects(lhs, reverse_rhs)) << info(i) << "Failed intersects(lhs, reverse_rhs)";
            ASSERT_EQ(expected, stf::alg::intersects(reverse_rhs, lhs)) << info(i) << "Failed intersects(reverse_rhs, lhs)";

            ASSERT_EQ(expected, stf::alg::intersects(reverse_lhs, reverse_rhs)) << info(i) << "Failed intersects(reverse_lhs, reverse_rhs)";
            ASSERT_EQ(expected, stf::alg::intersects(reverse_rhs, reverse_lhs)) << info(i) << "Failed intersects(reverse_rhs, reverse_lhs)";
        }
    };

    template<typename T>
    struct segment_with_aabb
    {
        stf::geom::segment2<T> seg;
        stf::geom::aabb2<T> box;
        bool expected;

        void verify(size_t const i) const
        {
            stf::geom::segment2<T> reverse_seg(seg.b, seg.a);

            ASSERT_EQ(expected, stf::alg::intersects(seg, box)) << info(i) << "Failed intersects(seg, box)";
            ASSERT_EQ(expected, stf::alg::intersects(box, seg)) << info(i) << "Failed intersects(box, seg)";

            ASSERT_EQ(expected, stf::alg::intersects(reverse_seg, box)) << info(i) << "Failed intersects(reverse_seg, box)";
            ASSERT_EQ(expected, stf::alg::intersects(box, reverse_seg)) << info(i) << "Failed intersects(box, reverse_seg)";
        }
    };

    template<typename T>
    struct polyline_with_aabb
    {
        stf::geom::polyline2<T> polyline;
        stf::geom::aabb2<T> box;
        bool expected;

        void verify(size_t const i) const
        {
            ASSERT_EQ(expected, stf::alg::intersects(polyline, box)) << info(i) << "Failed intersects(polyline, box)";
            ASSERT_EQ(expected, stf::alg::intersects(box, polyline)) << info(i) << "Failed intersects(box, polyline)";
        }
    };

    template<typename T>
    struct polygon_with_aabb
    {
        stf::geom::polygon<T> polygon;
        stf::geom::aabb2<T> box;
        bool expected;

        void verify(size_t const i) const
        {
            ASSERT_EQ(expected, stf::alg::intersects(polygon, box)) << info(i) << "Failed intersects(polygon, box)";
            ASSERT_EQ(expected, stf::alg::intersects(box, polygon)) << info(i) << "Failed intersects(box, polygon)";
        }
    };

    template<typename T>
    struct polygon_with_segment
    {
        stf::geom::polygon<T> polygon;
        stf::geom::segment2<T> segment;
        bool expected;

        void verify(size_t const i) const
        {
            ASSERT_EQ(expected, stf::alg::intersects(polygon, segment)) << info(i) << "Failed intersects(polygon, segment)";
            ASSERT_EQ(expected, stf::alg::intersects(segment, polygon)) << info(i) << "Failed intersects(segment, polygon)";
        }
    };

    template<typename T>
    struct polygon_with_polyline
    {
        stf::geom::polygon<T> polygon;
        stf::geom::polyline2<T> polyline;
        bool expected;

        void verify(size_t const i) const
        {
            ASSERT_EQ(expected, stf::alg::intersects(polygon, polyline)) << info(i) << "Failed intersects(polygon, polyline)";
            ASSERT_EQ(expected, stf::alg::intersects(polyline, polygon)) << info(i) << "Failed intersects(polyline, polygon)";
        }
    };

    template<typename T>
    struct ray_with_plane
    {
        stf::geom::ray3<T> ray;
        stf::geom::plane<T> plane;
        bool expected;

        void verify(size_t const i) const
        {
            stf::geom::plane<T> flipped = stf::geom::plane<T>(plane.point(), -plane.normal());

            ASSERT_EQ(expected, stf::alg::intersects(ray, plane)) << info(i) << "Failed intersects(ray, plane)";
            ASSERT_EQ(expected, stf::alg::intersects(plane, ray)) << info(i) << "Failed intersects(plane, ray)";

            ASSERT_EQ(expected, stf::alg::intersects(ray, flipped)) << info(i) << "Failed intersects(ray, flipped)";
            ASSERT_EQ(expected, stf::alg::intersects(flipped, ray)) << info(i) << "Failed intersects(flipped, ray)";
        }
    };

} // stf::scaffolding::alg::intersects