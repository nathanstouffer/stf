#include <vector>

#include <gtest/gtest.h>

#include <stf/types.h>

#include "scaffolding/vec.h"

namespace stf {
namespace math {

    TEST(vec2, index)
    {
        std::vector<scaffolding::vec::read<float, 2>> tests =
        {
            { stff::vec2(), { 0.f, 0.f } },
            { stff::vec2(1.f), { 1.f, 1.f } },
            { stff::vec2(1.f, 2.f), { 1.f, 2.f } },
        };

        for (scaffolding::vec::read<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, write)
    {
        std::vector<scaffolding::vec::write<float, 2>> tests =
        {
            { stff::vec2(), 0, 8.f },
            { stff::vec2(1.f, 2.f), 0, 10.f },
            { stff::vec2(1.f), 1, -5.f },
        };

        for (scaffolding::vec::write<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, plus_equals)
    {
        std::vector<scaffolding::vec::binary_op<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), stff::vec2() },
            { stff::vec2(), stff::vec2(1, 6), stff::vec2(1, 6) },
            { stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(5, 9) },
            { stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-4, -1) },
        };

        for (scaffolding::vec::binary_op<float, 2> const& test : tests)
        {
            stff::vec2 result = test.lhs;
            result += test.rhs;
            EXPECT_EQ(test.expected, result);
        }
    }

    TEST(vec2, minus_equals)
    {
        std::vector<scaffolding::vec::binary_op<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), stff::vec2() },
            { stff::vec2(), stff::vec2(1, 6), stff::vec2(-1, -6) },
            { stff::vec2(4, 3), stff::vec2(1, 6), stff::vec2(3, -3) },
            { stff::vec2(-5, -3), stff::vec2(1, 2), stff::vec2(-6, -5) },
        };

        for (scaffolding::vec::binary_op<float, 2> const& test : tests)
        {
            stff::vec2 result = test.lhs;
            result -= test.rhs;
            EXPECT_EQ(test.expected, result);
        }
    }

    TEST(vec2, scale_equals)
    {
        std::vector<scaffolding::vec::scale_equals<float, 2>> tests =
        {
            { stff::vec2(), 0, stff::vec2() },
            { stff::vec2(), 1, stff::vec2() },
            { stff::vec2(1, -1), 1, stff::vec2(1, -1) },
            { stff::vec2(1, -1), -1, stff::vec2(-1, 1) },
            { stff::vec2(1, -1), -2, stff::vec2(-2, 2) },
            { stff::vec2(2, -3), -2, stff::vec2(-4, 6) },
        };

        for (scaffolding::vec::scale_equals<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, equality)
    {
        std::vector<scaffolding::vec::equality<float, 2>> tests =
        {
            { stff::vec2(), stff::vec2(), true },
            { stff::vec2(0), stff::vec2(0), true },
            { stff::vec2(1), stff::vec2(1), true },
            { stff::vec2(2), stff::vec2(2), true },
            { stff::vec2(), stff::vec2(1), false },
            { stff::vec2(1), stff::vec2(2), false },
            { stff::vec2(2), stff::vec2(3), false },
            { stff::vec2(3), stff::vec2(4), false },
        };

        for (scaffolding::vec::equality<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

    TEST(vec2, negate)
    {
        std::vector<scaffolding::vec::negate<float, 2>> tests =
        {
            { stff::vec2() },
            { stff::vec2(1.f, 2.f) },
            { stff::vec2(1.f) },
        };

        for (scaffolding::vec::negate<float, 2> const& test : tests) { scaffolding::vec::verify(test); }
    }

} // math
} // stf