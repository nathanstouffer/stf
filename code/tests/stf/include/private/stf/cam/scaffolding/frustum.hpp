#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include <stf/alg/intersect.hpp>
#include <stf/cam/frustum.hpp>

namespace stf::cam::scaffolding::frustum
{

    template<typename T>
    struct contains
    {
        cam::frustum<T> const frustum;
        geom::aabb3<T> const box;
        bool const contains;
    };

    template<typename T>
    void verify(contains<T> const& test)
    {
        ASSERT_EQ(test.contains, test.frustum.contains(test.box)) << "Failed to compute frustum::contains(aabb)";
        ASSERT_EQ(test.contains, test.frustum.contains(geom::obb3<T>(test.box))) << "Failed to compute frustum::contains(obb)";
    }

    template<typename T>
    struct intersects_fast
    {
        cam::frustum<T> const frustum;
        geom::aabb3<T> const box;
        bool const intersects;
    };

    template<typename T>
    void verify(intersects_fast<T> const& test)
    {
        ASSERT_EQ(test.intersects, test.frustum.intersects_fast(test.box)) << "Failed to compute frustum::intersects_fast";
        ASSERT_EQ(test.intersects, alg::intersect_fast(test.frustum, test.box)) << "Failed to compute intersect_fast for frustum -> aabb";
        ASSERT_EQ(test.intersects, alg::intersect_fast(test.box, test.frustum)) << "Failed to compute intersect_fast for aabb -> frustum";
    }

    template<typename T>
    struct intersects
    {
        cam::frustum<T> const frustum;
        geom::aabb3<T> const box;
        bool const intersects;
    };

    template<typename T>
    void verify(intersects<T> const& test)
    {
        ASSERT_EQ(test.intersects, test.frustum.intersects(test.box)) << "Failed to compute frustum::intersects aabb";
        ASSERT_EQ(test.intersects, alg::intersect(test.frustum, test.box)) << "Failed to compute intersects for frustum -> aabb";
        ASSERT_EQ(test.intersects, alg::intersect(test.box, test.frustum)) << "Failed to compute intersects for aabb -> frustum";

        geom::obb3<T> obb(test.box);

        ASSERT_EQ(test.intersects, test.frustum.intersects(obb)) << "Failed to compute frustum::intersects obb";
        ASSERT_EQ(test.intersects, alg::intersect(test.frustum, obb)) << "Failed to compute intersects for frustum -> obb";
        ASSERT_EQ(test.intersects, alg::intersect(obb, test.frustum)) << "Failed to compute intersects for obb -> frustum";
    }

} // stf::cam::scaffolding::frustum