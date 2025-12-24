#ifndef STF_SCAFFOLDING_MATH_MATRIX_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_MATH_MATRIX_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/math/matrix.hpp>

namespace stf::scaffolding::math::mtx
{

template <typename T, size_t N>
struct equality
{
    stf::math::mtx<T, N> lhs;
    stf::math::mtx<T, N> rhs;
    bool equal;

    void verify(size_t const i) const
    {
        if (equal)
        {
            ASSERT_EQ(lhs, rhs) << info(i) << "failed positive assertion";
            ASSERT_FALSE(lhs != rhs) << info(i) << "failed negative assertion";
        }
        else
        {
            ASSERT_NE(lhs, rhs) << info(i) << "failed positive assertion";
            ASSERT_FALSE(lhs == rhs) << info(i) << "failed negative assertion";
        }
    }
};

template <typename T, size_t N>
struct determinant
{
    stf::math::mtx<T, N> matrix;
    T det;

    void verify(size_t const i) const { ASSERT_EQ(det, matrix.determinant()) << info(i) << "failed determinant test"; }
};

template <typename T, size_t N>
struct inverted
{
    stf::math::mtx<T, N> matrix;

    void verify(size_t const i) const
    {
        stf::math::mtx<T, N> identity = stf::math::mtx<T, N>();
        ASSERT_EQ(identity, matrix.inverted() * matrix)
            << info(i) << "failed " << N << "x" << N << " left inverse test";
        ASSERT_EQ(identity, matrix * matrix.inverted())
            << info(i) << "failed " << N << "x" << N << " right inverse test";
    }
};

} // namespace stf::scaffolding::math::mtx

#endif