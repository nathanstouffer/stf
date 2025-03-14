#pragma once

#include <gtest/gtest.h>

#include <stf/math/interval.hpp>

namespace stf::math::scaffolding::interval
{

    template<typename T>
    struct contains_point
    {
        math::interval<T> interval;
        boundary_types type;
        T x;
        bool contained;
    };

    template<typename T>
    void verify(contains_point<T> const& test)
    {
        ASSERT_EQ(test.contained, test.interval.contains(test.x, test.type)) << "failed contains point test";
    }

} // stf::math::scaffolding::interval