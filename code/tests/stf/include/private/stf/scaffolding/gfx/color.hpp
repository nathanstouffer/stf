#ifndef STF_SCAFFOLDING_GFX_COLOR_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_GFX_COLOR_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf::scaffolding::gfx::color
{

struct rgba_equality
{
    stf::gfx::rgba lhs;
    stf::gfx::rgba rhs;
    bool equal;

    void verify(size_t const i) const
    {
        if (equal)
        {
            ASSERT_EQ(lhs, rhs) << info(i) << "failed positive assertion";
            ASSERT_FALSE(lhs != rhs) << info(i) << "failed negative assertion";
            ASSERT_TRUE(equ(lhs, rhs, 0)) << info(i) << "failed exact positive assertion";
            ASSERT_FALSE(neq(lhs, rhs, 0)) << info(i) << "failed exact negative assertion";
        }
        else
        {
            ASSERT_NE(lhs, rhs) << info(i) << "failed positive assertion";
            ASSERT_FALSE(lhs == rhs) << info(i) << "failed negative assertion";
            ASSERT_TRUE(neq(lhs, rhs, 0)) << info(i) << "failed exact positive assertion";
            ASSERT_FALSE(equ(lhs, rhs, 0)) << info(i) << "failed exact negative assertion";
        }
    }
};

struct rgba_construct
{
    stf::gfx::rgba value;
    stf::gfx::rgba expected;

    void verify(size_t const i) const { ASSERT_EQ(expected, value) << info(i) << "failed to construct value"; }
};

struct component_to_hex
{
    float x;
    uint8_t expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::gfx::rgba::to_hex(x)) << info(i) << "Failed to compute hex correctly";
    }
};

struct component_from_hex
{
    uint32_t hex;
    uint32_t shift;
    float expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::gfx::rgba::from_hex(hex, shift)) << info(i) << "Failed to compute value correctly";
    }
};

struct rgba_hex_conversion
{
    uint32_t hex_rgba;
    uint32_t hex_abgr;
    uint32_t hex_argb;
    stf::gfx::rgba color;

    void verify(size_t const i) const
    {
        ASSERT_EQ(hex_rgba, color.to_hex_rgba()) << info(i) << "failed conversion to rgba";
        ASSERT_EQ(hex_abgr, color.to_hex_abgr()) << info(i) << "failed conversion to abgr";
        ASSERT_EQ(hex_argb, color.to_hex_argb()) << info(i) << "failed conversion to argb";

        ASSERT_EQ(color, stf::gfx::rgba::from_hex_rgba(hex_rgba)) << info(i) << "failed conversion from rgba";
        ASSERT_EQ(color, stf::gfx::rgba::from_hex_abgr(hex_abgr)) << info(i) << "failed conversion from abgr";
        ASSERT_EQ(color, stf::gfx::rgba::from_hex_argb(hex_argb)) << info(i) << "failed conversion from argb";
    }
};

} // namespace stf::scaffolding::gfx::color

#endif