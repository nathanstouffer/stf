#pragma once

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf {
namespace gfx {
namespace scaffolding {
namespace colors {

    struct equality
    {
        rgba const lhs;
        rgba const rhs;
        bool equal;
    };

    void verify(equality const& test)
    {
        if (test.equal)
        {
            ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
            ASSERT_TRUE(equ(test.lhs, test.rhs, rgba::num_t(0))) << "failed exact positive assertion";
            ASSERT_FALSE(neq(test.lhs, test.rhs, rgba::num_t(0))) << "failed exact negative assertion";
        }
        else
        {
            ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
            ASSERT_TRUE(neq(test.lhs, test.rhs, rgba::num_t(0))) << "failed exact positive assertion";
            ASSERT_FALSE(equ(test.lhs, test.rhs, rgba::num_t(0))) << "failed exact negative assertion";
        }
    }

    struct hex_conversion
    {
        uint32_t const hex_rgba;
        uint32_t const hex_abgr;
        uint32_t const hex_argb;
        rgba const color;
    };

    void verify(hex_conversion const& test)
    {
        ASSERT_EQ(test.hex_rgba, test.color.to_hex_rgba()) << "failed conversion to rgba";
        ASSERT_EQ(test.hex_abgr, test.color.to_hex_abgr()) << "failed conversion to abgr";
        ASSERT_EQ(test.hex_argb, test.color.to_hex_argb()) << "failed conversion to argb";

        ASSERT_EQ(test.color, rgba::from_hex_rgba(test.hex_rgba)) << "failed conversion from rgba";
        ASSERT_EQ(test.color, rgba::from_hex_abgr(test.hex_abgr)) << "failed conversion from abgr";
        ASSERT_EQ(test.color, rgba::from_hex_argb(test.hex_argb)) << "failed conversion from argb";
    }

} // colors
} // scaffolding
} // gfx
} // stf