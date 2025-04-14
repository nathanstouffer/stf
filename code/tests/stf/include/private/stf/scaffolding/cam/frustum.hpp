#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include <stf/alg/intersects.hpp>
#include <stf/cam/frustum.hpp>

namespace stf::scaffolding::cam::frustum
{

    template<typename T>
    struct contains
    {
        cam::frustum<T> frustum;
        geom::aabb3<T> box;
        bool contains;
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
        cam::frustum<T> frustum;
        geom::aabb3<T> box;
        bool intersects;
    };

    template<typename T>
    void verify(intersects_fast<T> const& test)
    {
        ASSERT_EQ(test.intersects, test.frustum.intersects_fast(test.box)) << "Failed to compute frustum::intersects_fast";
        ASSERT_EQ(test.intersects, alg::intersects_fast(test.frustum, test.box)) << "Failed to compute intersects_fast for frustum -> aabb";
        ASSERT_EQ(test.intersects, alg::intersects_fast(test.box, test.frustum)) << "Failed to compute intersects_fast for aabb -> frustum";
    }

    template<typename T>
    struct intersects
    {
        cam::frustum<T> frustum;
        geom::aabb3<T> box;
        bool intersects;
    };

    template<typename T>
    void verify(intersects<T> const& test)
    {
        ASSERT_EQ(test.intersects, test.frustum.intersects(test.box)) << "Failed to compute frustum::intersects aabb";
        ASSERT_EQ(test.intersects, alg::intersects(test.frustum, test.box)) << "Failed to compute intersects for frustum -> aabb";
        ASSERT_EQ(test.intersects, alg::intersects(test.box, test.frustum)) << "Failed to compute intersects for aabb -> frustum";

        geom::obb3<T> obb(test.box);

        ASSERT_EQ(test.intersects, test.frustum.intersects(obb)) << "Failed to compute frustum::intersects obb";
        ASSERT_EQ(test.intersects, alg::intersects(test.frustum, obb)) << "Failed to compute intersects for frustum -> obb";
        ASSERT_EQ(test.intersects, alg::intersects(obb, test.frustum)) << "Failed to compute intersects for obb -> frustum";
    }

} // stf::scaffolding::cam::frustum