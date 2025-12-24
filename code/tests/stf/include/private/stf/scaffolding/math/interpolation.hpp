#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/math/interpolation.hpp>

namespace stf::scaffolding::math::interpolation
{

template <typename T>
struct lerp
{
    T a;
    T b;
    T t;
    T expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::lerp(a, b, t)) << info(i) << "Failed to compute lerp";
    }
};

template <typename T>
struct lerp_inv
{
    T a;
    T b;
    T x;
    T expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::lerp_inv(a, b, x)) << info(i) << "Failed to compute lerp_inv";
    }
};

template <typename T>
struct lerpstep
{
    T a;
    T b;
    T t;
    T expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::lerpstep(a, b, t)) << info(i) << "Failed to compute lerp_step";
    }
};

} // namespace stf::scaffolding::math::interpolation