#ifndef STF_SCAFFOLDING_GEOM_AABB_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_GEOM_AABB_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/geom/aabb.hpp>
#include <stf/alg/intersects.hpp>
#include <stf/alg/containment.hpp>

namespace stf::scaffolding::geom::aabb
{

template <typename T, typename U, size_t N>
struct cast
{
    stf::geom::aabb<T, N> initial;

    void verify(size_t const i) const
    {
        stf::geom::aabb<U, N> result = initial.template as<U>();
        ASSERT_EQ(initial.min.template as<U>(), result.min) << info(i) << "Failed to cast properly";
        ASSERT_EQ(initial.max.template as<U>(), result.max) << info(i) << "Failed to cast properly";
    }
};

template <typename T, size_t N>
struct intersects
{
    stf::geom::aabb<T, N> lhs;
    stf::geom::aabb<T, N> rhs;
    bool intersect;

    void verify(size_t const i) const
    {
        ASSERT_EQ(intersect, lhs.intersects(rhs)) << info(i) << "failed lhs -> rhs intersection test (member)";
        ASSERT_EQ(intersect, rhs.intersects(lhs)) << info(i) << "failed rhs -> lhs intersection test (member)";

        ASSERT_EQ(intersect, alg::intersects(lhs, rhs)) << info(i) << "failed lhs -> rhs intersection test (free)";
        ASSERT_EQ(intersect, alg::intersects(rhs, lhs)) << info(i) << "failed rhs -> lhs intersection test (free)";
    }
};

template <typename T, size_t N>
struct contains
{
    stf::geom::aabb<T, N> lhs;
    stf::geom::aabb<T, N> rhs;
    bool contained;

    void verify(size_t const i) const
    {
        ASSERT_EQ(contained, lhs.contains(rhs)) << info(i) << "failed lhs -> rhs containment test (member)";
        ASSERT_EQ(contained, alg::contains(lhs, rhs)) << info(i) << "failed lhs -> rhs containment test (free)";
    }
};

template <typename T, size_t N>
struct dist_and_dist_squared
{
    stf::geom::aabb<T, N> box;
    stf::math::vec<T, N> point;
    T dist_squared;

    void verify(size_t const i) const
    {
        ASSERT_EQ(std::sqrt(dist_squared), box.dist(point)) << info(i) << "failed distance from aabb to vec";
        ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(box, point))
            << info(i) << "failed distance from aabb to vec";
        ASSERT_EQ(std::sqrt(dist_squared), stf::geom::dist(point, box))
            << info(i) << "failed distance from vec to aabb";

        ASSERT_EQ(dist_squared, box.dist_squared(point)) << info(i) << "failed distance squared from aabb to vec";
        ASSERT_EQ(dist_squared, stf::geom::dist_squared(box, point))
            << info(i) << "failed distance squared from aabb to vec";
        ASSERT_EQ(dist_squared, stf::geom::dist_squared(point, box))
            << info(i) << "failed distance squared from vec to aabb";
    }
};

} // namespace stf::scaffolding::geom::aabb

#endif