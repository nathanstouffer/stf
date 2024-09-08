#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include <stf/alg/intersection.hpp>
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
        ASSERT_EQ(test.contains, test.frustum.contains(test.box)) << "Failed to compute frustum::contains";
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
        ASSERT_EQ(test.intersects, alg::intersect_fast(test.frustum, test.box)) << "Failed to compute intersect_fast for frustum -> box";
        ASSERT_EQ(test.intersects, alg::intersect_fast(test.box, test.frustum)) << "Failed to compute intersect_fast for box -> frustum";
    }

} // stf::cam::scaffolding::frustum