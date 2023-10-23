#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/interpolation.hpp>

namespace stf {
namespace alg {
namespace scaffolding {
namespace interpolation {

    template<typename T>
    struct lerp
    {
        T const a;
        T const b;
        T const t;
        T const expected;
    };

    template<typename T>
    void verify(lerp<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::lerp(test.a, test.b, test.t)) << "Failed to compute lerp";
    }

    template<typename T>
    struct lerp_inv
    {
        T const a;
        T const b;
        T const x;
        T const expected;
    };

    template<typename T>
    void verify(lerp_inv<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::lerp_inv(test.a, test.b, test.x)) << "Failed to compute lerp_inv";
    }

    template<typename T>
    struct lerpstep
    {
        T const a;
        T const b;
        T const t;
        T const expected;
    };

    template<typename T>
    void verify(lerpstep<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::lerpstep(test.a, test.b, test.t)) << "Failed to compute lerp_step";
    }

} // interpolation
} // scaffolding
} // alg
} // stf