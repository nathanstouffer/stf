#pragma once

#include <gtest/gtest.h>

#include <stf/math/vector.h>

namespace stf {
namespace scaffolding {

    template<typename T, size_t N>
    struct vec_equality
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        bool equal;
    };

    template<typename T, size_t N>
    void verify(vec_equality<T, N> const& test)
    {
        if (test.equal)
        {
            ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
        }
        else
        {
            ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
        }
    }

} // scaffolding
} // stf