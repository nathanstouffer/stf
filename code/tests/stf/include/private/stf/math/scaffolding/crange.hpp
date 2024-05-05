#pragma once

#include <gtest/gtest.h>

#include <stf/math/crange.hpp>

namespace stf::math::scaffolding::crange
{

    template<typename T>
    struct contains_point
    {
        math::crange<T> const range;
        boundary const type;
        T const x;
        bool contained;
    };

    template<typename T>
    void verify(contains_point<T> const& test)
    {
        ASSERT_EQ(test.contained, test.range.contains(test.x, test.type)) << "failed contains point test";
    }

} // stf::math::scaffolding::crange