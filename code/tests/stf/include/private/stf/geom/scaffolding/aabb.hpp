#pragma once

#include <gtest/gtest.h>

#include <stf/geom/aabb.hpp>
#include <stf/alg/intersection.hpp>
#include <stf/alg/containment.hpp>

namespace stf::geom::scaffolding::aabb
{

    template<typename T, size_t N>
    struct intersects
    {
        geom::aabb<T, N> const lhs;
        geom::aabb<T, N> const rhs;
        bool intersect;
    };

    template<typename T, size_t N>
    void verify(intersects<T, N> const& test)
    {
        ASSERT_EQ(test.intersect, test.lhs.intersects(test.rhs)) << "failed lhs -> rhs intersection test (member)";
        ASSERT_EQ(test.intersect, test.rhs.intersects(test.lhs)) << "failed rhs -> lhs intersection test (member)";

        ASSERT_EQ(test.intersect, alg::intersect(test.lhs, test.rhs)) << "failed lhs -> rhs intersection test (free)";
        ASSERT_EQ(test.intersect, alg::intersect(test.rhs, test.lhs)) << "failed rhs -> lhs intersection test (free)";
    }

    template<typename T, size_t N>
    struct contains
    {
        geom::aabb<T, N> const lhs;
        geom::aabb<T, N> const rhs;
        bool contained;
    };

    template<typename T, size_t N>
    void verify(contains<T, N> const& test)
    {
        ASSERT_EQ(test.contained, test.lhs.contains(test.rhs)) << "failed lhs -> rhs containment test (member)";
        ASSERT_EQ(test.contained, alg::contains(test.lhs, test.rhs)) << "failed lhs -> rhs containment test (free)";
    }

} // stf::math::scaffolding::geom