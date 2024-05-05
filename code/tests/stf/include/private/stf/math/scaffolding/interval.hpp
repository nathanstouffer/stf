#pragma once

#include <gtest/gtest.h>

#include <stf/math/interval.hpp>

namespace stf::math::scaffolding::interval
{

    template<typename T>
    struct contains_point
    {
        math::interval<T> const interval;
        boundary_types const type;
        T const x;
        bool contained;
    };

    template<typename T>
    void verify(contains_point<T> const& test)
    {
        ASSERT_EQ(test.contained, test.interval.contains(test.x, test.type)) << "failed contains point test";
    }

} // stf::math::scaffolding::interval