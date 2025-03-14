#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/math/interpolation.hpp>

namespace stf::math::scaffolding::interpolation
{

    template<typename T>
    struct lerp
    {
        T a;
        T b;
        T t;
        T expected;
    };

    template<typename T>
    void verify(lerp<T> const& test)
    {
        ASSERT_EQ(test.expected, math::lerp(test.a, test.b, test.t)) << "Failed to compute lerp";
    }

    template<typename T>
    struct lerp_inv
    {
        T a;
        T b;
        T x;
        T expected;
    };

    template<typename T>
    void verify(lerp_inv<T> const& test)
    {
        ASSERT_EQ(test.expected, math::lerp_inv(test.a, test.b, test.x)) << "Failed to compute lerp_inv";
    }

    template<typename T>
    struct lerpstep
    {
        T a;
        T b;
        T t;
        T expected;
    };

    template<typename T>
    void verify(lerpstep<T> const& test)
    {
        ASSERT_EQ(test.expected, math::lerpstep(test.a, test.b, test.t)) << "Failed to compute lerp_step";
    }

} // stf::math::scaffolding::interpolation