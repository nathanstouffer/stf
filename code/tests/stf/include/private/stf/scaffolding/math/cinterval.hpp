#pragma once

#include <gtest/gtest.h>

#include <stf/math/cinterval.hpp>

namespace stf::scaffolding::math::cinterval
{

    template<typename T>
    struct contains_point
    {
        stf::math::cinterval<T> interval;
        boundary_types type;
        T x;
        bool contained;

        void verify(size_t const i) const
        {
            ASSERT_EQ(contained, interval.contains(x, type)) << info(i) << "failed contains point test";
        }
    };

} // stf::scaffolding::math::cinterval