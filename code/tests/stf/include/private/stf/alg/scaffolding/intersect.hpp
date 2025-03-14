#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/intersect.hpp>

namespace stf::alg::scaffolding::intersect
{

    template<typename T>
    struct segment_with_segment
    {
        geom::segment2<T> lhs;
        geom::segment2<T> rhs;
        bool expected;
    };

    template<typename T>
    void verify(segment_with_segment<T> const& test)
    {
        geom::segment2<T> reverse_lhs(test.lhs.b, test.lhs.a);
        geom::segment2<T> reverse_rhs(test.rhs.b, test.rhs.a);

        ASSERT_EQ(test.expected, alg::intersect(test.lhs, test.rhs)) << "Failed to intersect(lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersect(test.rhs, test.lhs)) << "Failed to intersect(rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersect(reverse_lhs, test.rhs)) << "Failed to intersect(reverse_lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersect(test.rhs, reverse_lhs)) << "Failed to intersect(rhs, reverse_lhs)";

        ASSERT_EQ(test.expected, alg::intersect(test.lhs, reverse_rhs)) << "Failed to intersect(lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersect(reverse_rhs, test.lhs)) << "Failed to intersect(reverse_rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersect(reverse_lhs, reverse_rhs)) << "Failed to intersect(reverse_lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersect(reverse_rhs, reverse_lhs)) << "Failed to intersect(reverse_rhs, reverse_lhs)";
    }

    template<typename T>
    struct segment_with_aabb
    {
        geom::segment2<T> seg;
        geom::aabb2<T> box;
        bool expected;
    };

    template<typename T>
    void verify(segment_with_aabb<T> const& test)
    {
        geom::segment2<T> reverse_seg(test.seg.b, test.seg.a);

        ASSERT_EQ(test.expected, alg::intersect(test.seg, test.box)) << "Failed to intersect(seg, box)";
        ASSERT_EQ(test.expected, alg::intersect(test.box, test.seg)) << "Failed to intersect(box, seg)";

        ASSERT_EQ(test.expected, alg::intersect(reverse_seg, test.box)) << "Failed to intersect(reverse_seg, box)";
        ASSERT_EQ(test.expected, alg::intersect(test.box, reverse_seg)) << "Failed to intersect(box, reverse_seg)";
    }

    template<typename T>
    struct polyline_with_aabb
    {
        geom::polyline2<T> polyline;
        geom::aabb2<T> box;
        bool expected;
    };

    template<typename T>
    void verify(polyline_with_aabb<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::intersect(test.polyline, test.box)) << "Failed to intersect(polyline, box)";
        ASSERT_EQ(test.expected, alg::intersect(test.box, test.polyline)) << "Failed to intersect(box, polyline)";
    }

    template<typename T>
    struct polygon_with_aabb
    {
        geom::polygon<T> polygon;
        geom::aabb2<T> box;
        bool expected;
    };

    template<typename T>
    void verify(polygon_with_aabb<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::intersect(test.polygon, test.box)) << "Failed to intersect(polygon, box)";
        ASSERT_EQ(test.expected, alg::intersect(test.box, test.polygon)) << "Failed to intersect(box, polygon)";
    }

    template<typename T>
    struct polygon_with_segment
    {
        geom::polygon<T> polygon;
        geom::segment2<T> segment;
        bool expected;
    };

    template<typename T>
    void verify(polygon_with_segment<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::intersect(test.polygon, test.segment)) << "Failed to intersect(polygon, segment)";
        ASSERT_EQ(test.expected, alg::intersect(test.segment, test.polygon)) << "Failed to intersect(segment, polygon)";
    }

    template<typename T>
    struct polygon_with_polyline
    {
        geom::polygon<T> polygon;
        geom::polyline2<T> polyline;
        bool expected;
    };

    template<typename T>
    void verify(polygon_with_polyline<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::intersect(test.polygon, test.polyline)) << "Failed to intersect(polygon, polyline)";
        ASSERT_EQ(test.expected, alg::intersect(test.polyline, test.polygon)) << "Failed to intersect(polyline, polygon)";
    }

} // stf::alg::scaffolding::intersection