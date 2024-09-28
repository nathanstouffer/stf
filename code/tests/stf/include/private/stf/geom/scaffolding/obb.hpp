#pragma once

#include <gtest/gtest.h>

#include <stf/geom/obb.hpp>
#include <stf/alg/intersection.hpp>
#include <stf/alg/containment.hpp>

namespace stf::geom::scaffolding::obb
{

    template<typename T, size_t N>
    struct intersect
    {
        geom::obb<T, N> const lhs;
        geom::obb<T, N> const rhs;
        bool intersect;
    };

    template<typename T, size_t N>
    void verify(intersect<T, N> const& test)
    {
        ASSERT_EQ(test.intersect, geom::intersect(test.lhs, test.rhs)) << "failed lhs -> rhs geom::intersect test";
        ASSERT_EQ(test.intersect, geom::intersect(test.rhs, test.lhs)) << "failed rhs -> lhs geom::intersect test";

        ASSERT_EQ(test.intersect, alg::intersect(test.lhs, test.rhs)) << "failed lhs -> rhs alg::intersect test";
        ASSERT_EQ(test.intersect, alg::intersect(test.rhs, test.lhs)) << "failed rhs -> lhs alg::intersect test";
    }

} // stf::geom::scaffolding::aabb