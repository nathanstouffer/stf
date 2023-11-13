#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/math/scaffolding/vector.hpp"

namespace stf {
namespace math {

    TEST(vec5, equality)
    {
        std::vector<scaffolding::vec::equality<float, 5>> tests =
        {
            { stff::vec<5>(), stff::vec<5>(), true },
            { stff::vec<5>(0.f), stff::vec<5>(0.f), true },
            { stff::vec<5>(1.f), stff::vec<5>(1.f), true },
            { stff::vec<5>(2.f), stff::vec<5>(2.f), true },
            { stff::vec<5>(), stff::vec<5>(1.f), false },
            { stff::vec<5>(1.f), stff::vec<5>(2.f), false },
            { stff::vec<5>(2.f), stff::vec<5>(3.f), false },
            { stff::vec<5>(3.f), stff::vec<5>(4.f), false },
        };

        for (scaffolding::vec::equality<float, 5> const& test : tests)
        {
            scaffolding::vec::verify(test);
        }
    }

    TEST(vec5, temp)
    {
        stf::math::temp result = stf::math::temp(1) + stf::math::temp(2);
        stf::math::temp other = plus(stf::math::temp(1), stf::math::temp(2));
        ASSERT_EQ(stf::math::temp(3), result) << "failed temp test";
        stf::math::foo<int>(0);
        stf::math::foo<float>(0);
        ASSERT_EQ(6, stf::math::simple_inc(5)) << "failed increment";
    }

} // math
} // stf