#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/intersection.hpp>

namespace stf::alg::scaffolding::intersection
{

    template<typename T>
    struct segment
    {
        math::segment2<T> const lhs;
        math::segment2<T> const rhs;
        bool const expected;
    };

    template<typename T>
    void verify(segment<T> const& test)
    {
        math::segment2<T> reverse_lhs(test.lhs.b, test.lhs.a);
        math::segment2<T> reverse_rhs(test.rhs.b, test.rhs.a);

        ASSERT_EQ(test.expected, alg::intersect(test.lhs, test.rhs)) << "Failed to intersect(lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersect(test.rhs, test.lhs)) << "Failed to intersect(rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersect(reverse_lhs, test.rhs)) << "Failed to intersect(reverse_lhs, rhs)";
        ASSERT_EQ(test.expected, alg::intersect(test.rhs, reverse_lhs)) << "Failed to intersect(rhs, reverse_lhs)";

        ASSERT_EQ(test.expected, alg::intersect(test.lhs, reverse_rhs)) << "Failed to intersect(lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersect(reverse_rhs, test.lhs)) << "Failed to intersect(reverse_rhs, lhs)";

        ASSERT_EQ(test.expected, alg::intersect(reverse_lhs, reverse_rhs)) << "Failed to intersect(reverse_lhs, reverse_rhs)";
        ASSERT_EQ(test.expected, alg::intersect(reverse_rhs, reverse_lhs)) << "Failed to intersect(reverse_rhs, reverse_lhs)";
    }

} // stf::alg::scaffolding::intersection