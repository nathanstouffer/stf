#pragma once

#include <gtest/gtest.h>

#include <stf/math/aabb.hpp>

namespace stf::math::scaffolding::aabb
{

    // TODO (stouff) change this to intersect
    template<typename T, size_t N>
    struct intersects
    {
        math::aabb<T, N> const lhs;
        math::aabb<T, N> const rhs;
        bool intersect;
    };

    template<typename T, size_t N>
    void verify(intersects<T, N> const& test)
    {
        ASSERT_EQ(test.intersect, test.lhs.intersects(test.rhs)) << "failed lhs -> rhs intersection test";
        ASSERT_EQ(test.intersect, test.rhs.intersects(test.lhs)) << "failed rhs -> lhs intersection test";
    }

} // stf::math::scaffolding::aabb