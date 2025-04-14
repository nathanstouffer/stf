#pragma once

#include <gtest/gtest.h>

#include <stf/geom/aabb.hpp>
#include <stf/alg/intersects.hpp>
#include <stf/alg/containment.hpp>

namespace stf::geom::scaffolding::aabb
{

    template<typename T, typename U, size_t N>
    struct cast
    {
        geom::aabb<T, N> initial;
    };

    template<typename T, typename U, size_t N>
    void verify(cast<T, U, N> const& test)
    {
        geom::aabb<U, N> result = test.initial.template as<U>();
        ASSERT_EQ(test.initial.min.template as<U>(), result.min) << "Failed to cast properly";
        ASSERT_EQ(test.initial.max.template as<U>(), result.max) << "Failed to cast properly";
    }

    template<typename T, size_t N>
    struct intersects
    {
        geom::aabb<T, N> lhs;
        geom::aabb<T, N> rhs;
        bool intersect;
    };

    template<typename T, size_t N>
    void verify(intersects<T, N> const& test)
    {
        ASSERT_EQ(test.intersect, test.lhs.intersects(test.rhs)) << "failed lhs -> rhs intersection test (member)";
        ASSERT_EQ(test.intersect, test.rhs.intersects(test.lhs)) << "failed rhs -> lhs intersection test (member)";

        ASSERT_EQ(test.intersect, alg::intersects(test.lhs, test.rhs)) << "failed lhs -> rhs intersection test (free)";
        ASSERT_EQ(test.intersect, alg::intersects(test.rhs, test.lhs)) << "failed rhs -> lhs intersection test (free)";
    }

    template<typename T, size_t N>
    struct contains
    {
        geom::aabb<T, N> lhs;
        geom::aabb<T, N> rhs;
        bool contained;
    };

    template<typename T, size_t N>
    void verify(contains<T, N> const& test)
    {
        ASSERT_EQ(test.contained, test.lhs.contains(test.rhs)) << "failed lhs -> rhs containment test (member)";
        ASSERT_EQ(test.contained, alg::contains(test.lhs, test.rhs)) << "failed lhs -> rhs containment test (free)";
    }

    template<typename T, size_t N>
    struct dist_and_dist_squared
    {
        geom::aabb<T, N> box;
        math::vec<T, N> point;
        T dist_squared;
    };

    template<typename T, size_t N>
    void verify(dist_and_dist_squared<T, N> const& test)
    {
        ASSERT_EQ(std::sqrt(test.dist_squared), test.box.dist(test.point)) << "failed distance from aabb to vec";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.box, test.point)) << "failed distance from aabb to vec";
        ASSERT_EQ(std::sqrt(test.dist_squared), geom::dist(test.point, test.box)) << "failed distance from vec to aabb";

        ASSERT_EQ(test.dist_squared, test.box.dist_squared(test.point)) << "failed distance squared from aabb to vec";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.box, test.point)) << "failed distance squared from aabb to vec";
        ASSERT_EQ(test.dist_squared, geom::dist_squared(test.point, test.box)) << "failed distance squared from vec to aabb";
    }

} // stf::geom::scaffolding::aabb