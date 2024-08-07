#include <vector>

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

#include <stf/gfx/scaffolding/color.hpp>

namespace stf::gfx
{

    TEST(rgba, equality)
    {
        std::vector<scaffolding::color::rgba_equality> tests =
        {
            { stf::gfx::rgba(), stf::gfx::rgba(), true },
            { stf::gfx::rgba(0), stf::gfx::rgba(0), true },
            { stf::gfx::rgba(1), stf::gfx::rgba(1), true },
            { stf::gfx::rgba(2), stf::gfx::rgba(2), true },
            { stf::gfx::rgba(), stf::gfx::rgba(1), false },
            { stf::gfx::rgba(1), stf::gfx::rgba(2), false },
            { stf::gfx::rgba(2), stf::gfx::rgba(3), false },
            { stf::gfx::rgba(3), stf::gfx::rgba(4), false },
        };

        for (scaffolding::color::rgba_equality const& test : tests) { scaffolding::color::verify(test); }
    }

    TEST(rgba, construct)
    {
        ASSERT_EQ(rgba(), rgba(0, 0, 0, 1)) << "Failed to construct default color";
        ASSERT_EQ(rgba(0.5), rgba(0.5, 0.5, 0.5, 0.5)) << "Failed to construct from single float";
        ASSERT_EQ(rgba(0.5, 0.75), rgba(0.5, 0.5, 0.5, 0.75)) << "Failed to construct from two floats";
        ASSERT_EQ(rgba(0.5, 0.75, 1.0), rgba(0.5, 0.75, 1.0, 1.0)) << "Failed to construct three floats";
        ASSERT_EQ(rgba(0.5, 0.75, 1.0, 0.25), rgba(0.5, 0.75, 1.0, 0.25)) << "Failed to construct four floats";
        ASSERT_EQ(rgba(math::vec<float, 3>(0.5, 0.75, 1.0)), rgba(0.5, 0.75, 1.0, 1.0)) << "Failed to construct from float vec3";
        ASSERT_EQ(rgba(math::vec<float, 4>(0.5, 0.75, 1.0, 0.25)), rgba(0.5, 0.75, 1.0, 0.25)) << "Failed to construct from float vec4";
    }
    
    TEST(rgba, component_to_hex)
    {
        struct test_t
        {
            float x;
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

        for (test_t const& test : tests) { ASSERT_EQ(test.expected, rgba::to_hex(test.x)) << "Failed to compute hex correctly"; }
    }

    TEST(rgba, component_from_hex)
    {
        struct test_t
        {
            uint32_t hex;
            uint32_t shift;
            float expected;
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

        for (test_t const& test : tests) { ASSERT_EQ(test.expected, rgba::from_hex(test.hex, test.shift)) << "Failed to compute value correctly"; }
    }

    TEST(rgba, hex_conversion)
    {
        std::vector<scaffolding::color::rgba_hex_conversion> tests =
        {
            // rgba         abgr            argb            color
            { 0x00000000,   0x00000000,     0x00000000,     rgba(0, 0, 0, 0) },
            { 0xFFFFFFFF,   0xFFFFFFFF,     0xFFFFFFFF,     rgba(1, 1, 1, 1) },
            { 0x00112233,   0x33221100,     0x33001122,     rgba(0, 0.06666666666, 0.13333333333, 0.2) },
            { 0xAABBCCDD,   0xDDCCBBAA,     0xDDAABBCC,     rgba(0.66666666666, 0.73333333333, 0.8, 0.86666666666) },
        };

        for (scaffolding::color::rgba_hex_conversion const& test : tests) { scaffolding::color::verify(test); }
    }

} // stf::gfx