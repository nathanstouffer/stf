#pragma once

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf {
namespace gfx {
namespace scaffolding {

    // TODO (stouff) probably set this up? but maybe not?
    // struct color_equality
    // {
    //     color const lhs;
    //     color const rhs;
    //     bool equal;
    // };

    // void verify(color_equality const& test)
    // {
    //     if (test.equal)
    //     {
    //         ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
    //         ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
    //         ASSERT_TRUE(math::equ(test.lhs, test.rhs, T(0))) << "failed exact positive assertion";
    //         ASSERT_FALSE(math::neq(test.lhs, test.rhs, T(0))) << "failed exact negative assertion";
    //     }
    //     else
    //     {
    //         ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
    //         ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
    //         ASSERT_TRUE(math::neq(test.lhs, test.rhs, T(0))) << "failed exact positive assertion";
    //         ASSERT_FALSE(math::equ(test.lhs, test.rhs, T(0))) << "failed exact negative assertion";
    //     }
    // }

} // scaffolding
} // gfx
} // stf