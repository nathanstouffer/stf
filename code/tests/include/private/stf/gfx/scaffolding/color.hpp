#pragma once

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf {
namespace gfx {
namespace scaffolding {
namespace colors {

    struct equality
    {
        color const lhs;
        color const rhs;
        bool equal;
    };

    void verify(equality const& test)
    {
        if (test.equal)
        {
            ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
            ASSERT_TRUE(equ(test.lhs, test.rhs, color::num_t(0))) << "failed exact positive assertion";
            ASSERT_FALSE(neq(test.lhs, test.rhs, color::num_t(0))) << "failed exact negative assertion";
        }
        else
        {
            ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
            ASSERT_TRUE(neq(test.lhs, test.rhs, color::num_t(0))) << "failed exact positive assertion";
            ASSERT_FALSE(equ(test.lhs, test.rhs, color::num_t(0))) << "failed exact negative assertion";
        }
    }

    struct hex_conversion
    {
        uint32_t const rgba;
        uint32_t const abgr;
        uint32_t const argb;
        color const color;
    };

    void verify(hex_conversion const& test)
    {
        ASSERT_EQ(test.rgba, test.color.rgba()) << "failed conversion to rgba";
        ASSERT_EQ(test.abgr, test.color.abgr()) << "failed conversion to abgr";
        ASSERT_EQ(test.argb, test.color.argb()) << "failed conversion to argb";

        ASSERT_EQ(test.color, color::from_rgba(test.rgba)) << "failed conversion from rgba";
        ASSERT_EQ(test.color, color::from_abgr(test.abgr)) << "failed conversion from abgr";
        ASSERT_EQ(test.color, color::from_argb(test.argb)) << "failed conversion from argb";
    }

} // colors
} // scaffolding
} // gfx
} // stf