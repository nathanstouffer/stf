#include <vector>

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

namespace stf {
namespace gfx {

    // TODO (stouff) possibly move the test struct declarations into the scaffolding directory?
    // it's kind of more a thing for vector because of the templated N param
    
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

} // gfx
} // stf