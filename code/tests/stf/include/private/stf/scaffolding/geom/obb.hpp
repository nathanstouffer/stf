#ifndef STF_SCAFFOLDING_GEOM_OBB_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_GEOM_OBB_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/geom/obb.hpp>
#include <stf/alg/intersects.hpp>
#include <stf/alg/containment.hpp>

namespace stf::scaffolding::geom::obb
{

template <typename T, size_t N>
struct from_aabb
{
    stf::geom::aabb<T, N> aabb;

    void verify(size_t const i) const
    {
        stf::geom::obb<T, N> obb(aabb);

        for (size_t v = 0; v < stf::geom::obb<T, N>::vertex_count(); ++v)
        {
            ASSERT_EQ(aabb.vertex(v), obb.vertex(v)) << info(i) << "failed vertex equality for v = " << v;
        }
    }
};

template <typename T, size_t N>
struct extremity
{
    stf::geom::obb<T, N> obb;
    stf::math::vec<T, N> axis;
    stf::math::vec<T, N> extreme;

    void verify(size_t const i) const
    {
        ASSERT_EQ(extreme, obb.extremity(axis)) << info(i) << "failed to compute extremity";
    }
};

template <typename T, size_t N>
struct contains
{
    stf::geom::obb<T, N> obb;
    stf::math::vec<T, N> point;
    bool contains;

    void verify(size_t const i) const
    {
        ASSERT_EQ(contains, obb.contains(point)) << info(i) << "failed point in obb test";
    }
};

template <typename T, size_t N>
struct fit
{
    stf::math::mtx<T, N> rotation;
    T half_extent;

    void verify(size_t const i) const
    {
        stf::geom::obb<T, N> constructed(stf::math::vec<T, N>(0), rotation, stf::math::vec<T, N>(half_extent));

        stf::geom::obb<T, N> fitted(rotation);
        for (math::vec<T, N> const& direction : math::canonical_basis<T, N>())
        {
            fitted.fit(half_extent * (rotation * direction));
            fitted.fit(-half_extent * (rotation * direction));
        }

        for (size_t v = 0; v < stf::geom::obb<T, N>::vertex_count(); ++v)
        {
            ASSERT_EQ(constructed.vertex(v), fitted.vertex(v)) << info(i) << "failed vertex equality for v = " << v;
        }
    }
};

template <typename T, size_t N>
struct intersect
{
    stf::geom::obb<T, N> lhs;
    stf::geom::obb<T, N> rhs;
    bool intersect;

    void verify(size_t const i) const
    {
        ASSERT_EQ(intersect, stf::geom::intersects(lhs, rhs)) << info(i) << "failed lhs -> rhs geom::intersect test";
        ASSERT_EQ(intersect, stf::geom::intersects(rhs, lhs)) << info(i) << "failed rhs -> lhs geom::intersect test";

        ASSERT_EQ(intersect, stf::alg::intersects(lhs, rhs)) << info(i) << "failed lhs -> rhs alg::intersect test";
        ASSERT_EQ(intersect, stf::alg::intersects(rhs, lhs)) << info(i) << "failed rhs -> lhs alg::intersect test";
    }
};

} // namespace stf::scaffolding::geom::obb

#endif