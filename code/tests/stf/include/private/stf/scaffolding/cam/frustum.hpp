#ifndef STF_SCAFFOLDING_CAM_FRUSTUM_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_CAM_FRUSTUM_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include <stf/alg/intersects.hpp>
#include <stf/cam/frustum.hpp>

namespace stf::scaffolding::cam::frustum
{

template <typename T>
struct contains
{
    stf::cam::frustum<T> frustum;
    stf::geom::aabb3<T> box;
    bool contains;

    void verify(size_t const i) const
    {
        ASSERT_EQ(contains, frustum.contains(box)) << info(i) << "Failed to compute frustum::contains(aabb)";
        ASSERT_EQ(contains, frustum.contains(stf::geom::obb3<T>(box)))
            << info(i) << "Failed to compute frustum::contains(obb)";
    }
};

template <typename T>
struct intersects_fast
{
    stf::cam::frustum<T> frustum;
    stf::geom::aabb3<T> box;
    bool intersects;

    void verify(size_t const i) const
    {
        ASSERT_EQ(intersects, frustum.intersects_fast(box)) << info(i) << "Failed to compute frustum::intersects_fast";
        ASSERT_EQ(intersects, stf::alg::intersects_fast(frustum, box))
            << info(i) << "Failed to compute intersects_fast for frustum -> aabb";
        ASSERT_EQ(intersects, stf::alg::intersects_fast(box, frustum))
            << info(i) << "Failed to compute intersects_fast for aabb -> frustum";
    }
};

template <typename T>
struct intersects
{
    stf::cam::frustum<T> frustum;
    stf::geom::aabb3<T> box;
    bool intersects;

    void verify(size_t const i) const
    {
        ASSERT_EQ(intersects, frustum.intersects(box)) << info(i) << "Failed to compute frustum::intersects aabb";
        ASSERT_EQ(intersects, stf::alg::intersects(frustum, box))
            << info(i) << "Failed to compute intersects for frustum -> aabb";
        ASSERT_EQ(intersects, stf::alg::intersects(box, frustum))
            << info(i) << "Failed to compute intersects for aabb -> frustum";

        stf::geom::obb3<T> obb(box);

        ASSERT_EQ(intersects, frustum.intersects(obb)) << info(i) << "Failed to compute frustum::intersects obb";
        ASSERT_EQ(intersects, stf::alg::intersects(frustum, obb))
            << info(i) << "Failed to compute intersects for frustum -> obb";
        ASSERT_EQ(intersects, stf::alg::intersects(obb, frustum))
            << info(i) << "Failed to compute intersects for obb -> frustum";
    }
};

} // namespace stf::scaffolding::cam::frustum

#endif