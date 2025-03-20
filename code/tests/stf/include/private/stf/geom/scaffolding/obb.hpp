#pragma once

#include <gtest/gtest.h>

#include <stf/geom/obb.hpp>
#include <stf/alg/intersects.hpp>
#include <stf/alg/containment.hpp>

namespace stf::geom::scaffolding::obb
{

    template<typename T, size_t N>
    struct from_aabb
    {
        geom::aabb<T, N> aabb;
    };

    template<typename T, size_t N>
    void verify(from_aabb<T, N> const& test)
    {
        geom::obb<T, N> obb(test.aabb);

        for (size_t v = 0; v < geom::obb<T, N>::vertex_count(); ++v)
        {
            ASSERT_EQ(test.aabb.vertex(v), obb.vertex(v)) << "failed vertex equality for v = " << v;
        }
    }

    template<typename T, size_t N>
    struct extremity
    {
        geom::obb<T, N> obb;
        math::vec<T, N> axis;
        math::vec<T, N> extreme;
    };

    template<typename T, size_t N>
    void verify(extremity<T, N> const& test)
    {
        ASSERT_EQ(test.extreme, test.obb.extremity(test.axis)) << "failed to compute extremity";
    }

    template<typename T, size_t N>
    struct contains
    {
        geom::obb<T, N> obb;
        math::vec<T, N> point;
        bool contains;
    };

    template<typename T, size_t N>
    void verify(contains<T, N> const& test)
    {
        ASSERT_EQ(test.contains, test.obb.contains(test.point)) << "failed point in obb test";
    }

    template<typename T, size_t N>
    struct fit
    {
        math::mtx<T, N> rotation;
        T half_extent;
    };

    template<typename T, size_t N>
    void verify(fit<T, N> const& test)
    {
        geom::obb<T, N> constructed(math::vec<T, N>(0), test.rotation, math::vec<T, N>(test.half_extent));

        geom::obb<T, N> fitted(test.rotation);
        for (math::vec<T, N> const& direction : math::canonical_basis<T, N>())
        {
            fitted.fit( test.half_extent * (test.rotation * direction));
            fitted.fit(-test.half_extent * (test.rotation * direction));
        }

        for (size_t v = 0; v < geom::obb<T, N>::vertex_count(); ++v)
        {
            ASSERT_EQ(constructed.vertex(v), fitted.vertex(v)) << "failed vertex equality for v = " << v;
        }
    }

    template<typename T, size_t N>
    struct intersect
    {
        geom::obb<T, N> lhs;
        geom::obb<T, N> rhs;
        bool intersect;
    };

    template<typename T, size_t N>
    void verify(intersect<T, N> const& test)
    {
        ASSERT_EQ(test.intersect, geom::intersects(test.lhs, test.rhs)) << "failed lhs -> rhs geom::intersect test";
        ASSERT_EQ(test.intersect, geom::intersects(test.rhs, test.lhs)) << "failed rhs -> lhs geom::intersect test";

        ASSERT_EQ(test.intersect, alg::intersects(test.lhs, test.rhs)) << "failed lhs -> rhs alg::intersect test";
        ASSERT_EQ(test.intersect, alg::intersects(test.rhs, test.lhs)) << "failed rhs -> lhs alg::intersect test";
    }

} // stf::geom::scaffolding::aabb