#include <vector>

#include <gtest/gtest.h>

#include <stf/gfx/color.hpp>

#include <stf/scaffolding/gfx/color.hpp>
#include "stf/scaffolding/verify.hpp"

namespace stf::gfx
{

TEST(rgba, equality)
{
    std::vector<scaffolding::gfx::color::rgba_equality> tests = {
        {stf::gfx::rgba(), stf::gfx::rgba(), true},
        {stf::gfx::rgba(0), stf::gfx::rgba(0), true},
        {stf::gfx::rgba(1), stf::gfx::rgba(1), true},
        {stf::gfx::rgba(2), stf::gfx::rgba(2), true},
        {stf::gfx::rgba(), stf::gfx::rgba(1), false},
        {stf::gfx::rgba(1), stf::gfx::rgba(2), false},
        {stf::gfx::rgba(2), stf::gfx::rgba(3), false},
        {stf::gfx::rgba(3), stf::gfx::rgba(4), false},
    };
    scaffolding::verify(tests);
}

TEST(rgba, construct)
{
    std::vector<scaffolding::gfx::color::rgba_construct> tests = {
        {rgba(), rgba(0, 0, 0, 1)},
        {rgba(0.5f), rgba(0.5f, 0.5f, 0.5f, 0.5f)},
        {rgba(0.5f, 0.75f), rgba(0.5f, 0.5f, 0.5f, 0.75f)},
        {rgba(0.5f, 0.75f, 1.0f), rgba(0.5f, 0.75f, 1.0f, 1.0f)},
        {rgba(0.5f, 0.75f, 1.0f, 0.25f), rgba(0.5f, 0.75f, 1.0f, 0.25f)},
        {rgba(math::vec<float, 3>(0.5f, 0.75f, 1.0f)), rgba(0.5f, 0.75f, 1.0f, 1.0f)},
        {rgba(math::vec<float, 4>(0.5f, 0.75f, 1.0f, 0.25f)), rgba(0.5f, 0.75f, 1.0f, 0.25f)},
    };
    scaffolding::verify(tests);
}

TEST(rgba, component_to_hex)
{
    std::vector<scaffolding::gfx::color::component_to_hex> tests = {
        {0, 0}, {1, 255}, {-0.1f, 0}, {-1, 0}, {1.1f, 255}, {2, 255}, {0.5f, 128},
    };
    scaffolding::verify(tests);
}

TEST(rgba, component_from_hex)
{
    std::vector<scaffolding::gfx::color::component_from_hex> tests = {
        {0x00000000, 0, 0},
        {0x00000000, 8, 0},
        {0x00000000, 16, 0},
        {0x00000000, 24, 0},
        {0xFFFFFFFF, 0, 1},
        {0xFFFFFFFF, 8, 1},
        {0xFFFFFFFF, 16, 1},
        {0xFFFFFFFF, 24, 1},
        {0xC0804000, 0, 0},
        {0xC0804000, 8, 0.25098039215f},
        {0xC0804000, 16, 0.50196078431f},
        {0xC0804000, 24, 0.75294117647f},
    };
    scaffolding::verify(tests);
}

TEST(rgba, hex_conversion)
{
    std::vector<scaffolding::gfx::color::rgba_hex_conversion> tests = {
        // rgba         abgr            argb            color
        {0x00000000, 0x00000000, 0x00000000, rgba(0, 0, 0, 0)},
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, rgba(1, 1, 1, 1)},
        {0x00112233, 0x33221100, 0x33001122, rgba(0, 0.06666666666f, 0.13333333333f, 0.2f)},
        {0xAABBCCDD, 0xDDCCBBAA, 0xDDAABBCC,
         rgba(0.66666666666f, 0.73333333333f, 0.8f, 0.86666666666f)},
    };
    scaffolding::verify(tests);
}

} // namespace stf::gfx