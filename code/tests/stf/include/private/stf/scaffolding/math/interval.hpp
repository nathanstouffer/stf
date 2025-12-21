#pragma once

#include <gtest/gtest.h>

#include <stf/math/interval.hpp>

namespace stf::scaffolding::math::interval
{

template <typename T>
struct contains_point
{
    stf::math::interval<T> interval;
    boundary_types type;
    T x;
    bool contained;

    void verify(size_t const i) const
    {
        ASSERT_EQ(contained, interval.contains(x, type)) << info(i) << "failed contains point test";
    }
};

} // namespace stf::scaffolding::math::interval