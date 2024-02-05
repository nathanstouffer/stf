#pragma once

#include <gtest/gtest.h>

#include <stf/math/range.hpp>

namespace stf::math::scaffolding::range
{

    template<typename T>
    struct contains_point
    {
        math::range<T> const range;
        endpoints const type;
        T const x;
        bool contained;
    };

    template<typename T>
    void verify(contains_point<T> const& test)
    {
        ASSERT_EQ(test.contained, test.range.contains(test.x, test.type)) << "failed contains point test";
    }

} // stf::math::scaffolding::range