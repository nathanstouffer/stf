#include <vector>

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

#include <stf/gfx/scaffolding/color.hpp>

namespace stf {
namespace gfx {

    TEST(color, equality)
    {
        std::vector<scaffolding::colors::equality> tests =
        {
            { stf::gfx::color(), stf::gfx::color(), true },
            { stf::gfx::color(0), stf::gfx::color(0), true },
            { stf::gfx::color(1), stf::gfx::color(1), true },
            { stf::gfx::color(2), stf::gfx::color(2), true },
            { stf::gfx::color(), stf::gfx::color(1), false },
            { stf::gfx::color(1), stf::gfx::color(2), false },
            { stf::gfx::color(2), stf::gfx::color(3), false },
            { stf::gfx::color(3), stf::gfx::color(4), false },
        };

        for (scaffolding::colors::equality const& test : tests) { scaffolding::colors::verify(test); }
    }

    TEST(color, construct)
    {
        ASSERT_EQ(color(), color(0, 0, 0, 1)) << "Failed to construct default color";
        ASSERT_EQ(color(0.5), color(0.5, 0.5, 0.5, 0.5)) << "Failed to construct from single float";
        ASSERT_EQ(color(0.5, 0.75), color(0.5, 0.5, 0.5, 0.75)) << "Failed to construct from two floats";
        ASSERT_EQ(color(0.5, 0.75, 1.0), color(0.5, 0.75, 1.0, 1.0)) << "Failed to construct three floats";
        ASSERT_EQ(color(0.5, 0.75, 1.0, 0.25), color(0.5, 0.75, 1.0, 0.25)) << "Failed to construct four floats";
        ASSERT_EQ(color(math::vec<float, 3>(0.5, 0.75, 1.0)), color(0.5, 0.75, 1.0, 1.0)) << "Failed to construct from float vec3";
        ASSERT_EQ(color(math::vec<float, 4>(0.5, 0.75, 1.0, 0.25)), color(0.5, 0.75, 1.0, 0.25)) << "Failed to construct from float vec4";
    }
    
    TEST(color, to_byte)
    {
        struct test_t
        {
            color::num_t x;
            uint8_t expected;
        };

        std::vector<test_t> tests =
        {
            { 0, 0 },
            { 1, 255 },
            { -0.1, 0 },
            { -1, 0 },
            { 1.1, 255 },
            { 2, 255 },
            { 0.5, 128 },
        };

        for (test_t const& test : tests) { ASSERT_EQ(test.expected, color::to_byte(test.x)) << "Failed to compute byte correctly"; }
    }

    TEST(color, from_byte)
    {
        struct test_t
        {
            uint32_t hex;
            uint32_t shift;
            color::num_t expected;
        };

        std::vector<test_t> tests =
        {
            { 0x00000000, 0, 0 },
            { 0x00000000, 8, 0 },
            { 0x00000000, 16, 0 },
            { 0x00000000, 24, 0 },
            { 0xFFFFFFFF, 0, 1 },
            { 0xFFFFFFFF, 8, 1 },
            { 0xFFFFFFFF, 16, 1 },
            { 0xFFFFFFFF, 24, 1 },
            { 0xC0804000, 0, 0 },
            { 0xC0804000, 8, 0.25098039215 },
            { 0xC0804000, 16, 0.50196078431 },
            { 0xC0804000, 24, 0.75294117647 },
        };

        for (test_t const& test : tests) { ASSERT_EQ(test.expected, color::from_byte(test.hex, test.shift)) << "Failed to compute value correctly"; }
    }

    TEST(color, hex_conversion)
    {
        std::vector<scaffolding::colors::hex_conversion> tests =
        {
            // rgba         abgr            argb            color
            { 0x00000000,   0x00000000,     0x00000000,     color(0, 0, 0, 0) },
            { 0xFFFFFFFF,   0xFFFFFFFF,     0xFFFFFFFF,     color(1, 1, 1, 1) },
            { 0x00112233,   0x33221100,     0x33001122,     color(0, 0.06666666666, 0.13333333333, 0.2) },
            { 0xAABBCCDD,   0xDDCCBBAA,     0xDDAABBCC,     color(0.66666666666, 0.73333333333, 0.8, 0.86666666666) },
        };

        for (scaffolding::colors::hex_conversion const& test : tests) { scaffolding::colors::verify(test); }
    }

} // gfx
} // stf