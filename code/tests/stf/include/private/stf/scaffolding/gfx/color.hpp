#pragma once

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf::scaffolding::gfx::color
{

    struct rgba_equality
    {
        rgba lhs;
        rgba rhs;
        bool equal;
    };

    void verify(rgba_equality const& test)
    {
        if (test.equal)
        {
            ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
            ASSERT_TRUE(equ(test.lhs, test.rhs, 0)) << "failed exact positive assertion";
            ASSERT_FALSE(neq(test.lhs, test.rhs, 0)) << "failed exact negative assertion";
        }
        else
        {
            ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
            ASSERT_TRUE(neq(test.lhs, test.rhs, 0)) << "failed exact positive assertion";
            ASSERT_FALSE(equ(test.lhs, test.rhs, 0)) << "failed exact negative assertion";
        }
    }

    struct rgba_hex_conversion
    {
        uint32_t hex_rgba;
        uint32_t hex_abgr;
        uint32_t hex_argb;
        rgba color;
    };

    void verify(rgba_hex_conversion const& test)
    {
        ASSERT_EQ(test.hex_rgba, test.color.to_hex_rgba()) << "failed conversion to rgba";
        ASSERT_EQ(test.hex_abgr, test.color.to_hex_abgr()) << "failed conversion to abgr";
        ASSERT_EQ(test.hex_argb, test.color.to_hex_argb()) << "failed conversion to argb";

        ASSERT_EQ(test.color, rgba::from_hex_rgba(test.hex_rgba)) << "failed conversion from rgba";
        ASSERT_EQ(test.color, rgba::from_hex_abgr(test.hex_abgr)) << "failed conversion from abgr";
        ASSERT_EQ(test.color, rgba::from_hex_argb(test.hex_argb)) << "failed conversion from argb";
    }

} // stf::scaffolding::gfx::color