#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/intersection.hpp>

namespace stf::alg::scaffolding::intersection
{

    template<typename T>
    struct segment_with_segment
    {
        geom::segment2<T> const lhs;
        geom::segment2<T> const rhs;
        bool const expected;
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
        geom::segment2<T> const seg;
        geom::aabb2<T> const box;
        bool const expected;
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

} // stf::alg::scaffolding::intersection