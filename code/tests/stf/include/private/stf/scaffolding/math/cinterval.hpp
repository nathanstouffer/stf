#ifndef STF_SCAFFOLDING_MATH_CINTERVAL_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_MATH_CINTERVAL_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/math/cinterval.hpp>

namespace stf::scaffolding::math::cinterval
{

template <typename T>
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

} // namespace stf::scaffolding::math::cinterval
#endif
