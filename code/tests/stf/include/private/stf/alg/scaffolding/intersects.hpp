#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/intersects.hpp>

namespace stf::alg::scaffolding::intersects
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

        ASSERT_EQ(test.expected, alg::intersects(test.lhs, test.rhs)) << "Failed intersects(lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersects(test.rhs, test.lhs)) << "Failed intersects(rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersects(reverse_lhs, test.rhs)) << "Failed intersects(reverse_lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersects(test.rhs, reverse_lhs)) << "Failed intersects(rhs, reverse_lhs)";

        ASSERT_EQ(test.expected, alg::intersects(test.lhs, reverse_rhs)) << "Failed intersects(lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersects(reverse_rhs, test.lhs)) << "Failed intersects(reverse_rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersects(reverse_lhs, reverse_rhs)) << "Failed intersects(reverse_lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersects(reverse_rhs, reverse_lhs)) << "Failed intersects(reverse_rhs, reverse_lhs)";
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

        ASSERT_EQ(test.expected, alg::intersects(test.seg, test.box)) << "Failed intersects(seg, box)";
        ASSERT_EQ(test.expected, alg::intersects(test.box, test.seg)) << "Failed intersects(box, seg)";

        ASSERT_EQ(test.expected, alg::intersects(reverse_seg, test.box)) << "Failed intersects(reverse_seg, box)";
        ASSERT_EQ(test.expected, alg::intersects(test.box, reverse_seg)) << "Failed intersects(box, reverse_seg)";
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
        ASSERT_EQ(test.expected, alg::intersects(test.polyline, test.box)) << "Failed intersects(polyline, box)";
        ASSERT_EQ(test.expected, alg::intersects(test.box, test.polyline)) << "Failed intersects(box, polyline)";
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
        ASSERT_EQ(test.expected, alg::intersects(test.polygon, test.box)) << "Failed intersects(polygon, box)";
        ASSERT_EQ(test.expected, alg::intersects(test.box, test.polygon)) << "Failed intersects(box, polygon)";
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
        ASSERT_EQ(test.expected, alg::intersects(test.polygon, test.segment)) << "Failed intersects(polygon, segment)";
        ASSERT_EQ(test.expected, alg::intersects(test.segment, test.polygon)) << "Failed intersects(segment, polygon)";
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
        ASSERT_EQ(test.expected, alg::intersects(test.polygon, test.polyline)) << "Failed intersects(polygon, polyline)";
        ASSERT_EQ(test.expected, alg::intersects(test.polyline, test.polygon)) << "Failed intersects(polyline, polygon)";
    }

} // stf::alg::scaffolding::intersection