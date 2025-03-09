#pragma once

#include <gtest/gtest.h>

#include <stf/math/matrix.hpp>

namespace stf::math::scaffolding::mtx
{

    template<typename T, size_t N>
    struct equality
    {
        math::mtx<T, N> lhs;
        math::mtx<T, N> rhs;
        bool equal;
    };

    template<typename T, size_t N>
    void verify(equality<T, N> const& test)
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

    template<typename T, size_t N>
    struct determinant
    {
        math::mtx<T, N> matrix;
        T det;
    };

    template<typename T, size_t N>
    void verify(determinant<T, N> const& test)
    {
        ASSERT_EQ(test.det, test.matrix.determinant()) << "failed determinant test";
    }

    template<typename T, size_t N>
    struct inverse
    {
        math::mtx<T, N> matrix;
    };

    template<typename T, size_t N>
    void verify(inverse<T, N> const& test)
    {
        math::mtx<T, N> identity = math::mtx<T, N>();
        ASSERT_EQ(identity, test.matrix.inverted() * test.matrix) << "failed " << N << "x" << N << " left inverse test";
        ASSERT_EQ(identity, test.matrix * test.matrix.inverted()) << "failed " << N << "x" << N << " right inverse test";
    }

} // stf::math::scaffolding::interval