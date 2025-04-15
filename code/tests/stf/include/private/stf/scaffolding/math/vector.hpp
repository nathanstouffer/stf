#pragma once

#include <gtest/gtest.h>

#include <stf/math/vector.hpp>

namespace stf::scaffolding::math::vec
{

    template<typename T, size_t N>
    struct equality
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        bool equal;

        void verify(size_t const i) const
        {
            if (equal)
            {
                ASSERT_EQ(lhs, rhs) << info(i) << "failed positive assertion";
                ASSERT_FALSE(lhs != rhs) << info(i) << "failed negative assertion";
                ASSERT_TRUE(stf::math::equ(lhs, rhs, stf::math::constants<T>::zero)) << info(i) << "failed exact positive assertion";
                ASSERT_FALSE(stf::math::neq(lhs, rhs, stf::math::constants<T>::zero)) << info(i) << "failed exact negative assertion";
            }
            else
            {
                ASSERT_NE(lhs, rhs) << info(i) << "failed positive assertion";
                ASSERT_FALSE(lhs == rhs) << info(i) << "failed negative assertion";
                ASSERT_TRUE(stf::math::neq(lhs, rhs, stf::math::constants<T>::zero)) << info(i) << "failed exact positive assertion";
                ASSERT_FALSE(stf::math::equ(lhs, rhs, stf::math::constants<T>::zero)) << info(i) << "failed exact negative assertion";
            }
        }

    };

    template<typename T, size_t N>
    struct read
    {
        stf::math::vec<T, N> lhs;
        T expected[N];

        void verify(size_t const index) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                ASSERT_EQ(expected[i], lhs[i]) << info(index);
            }

            if constexpr (N == 2)
            {
                ASSERT_EQ(expected[0], lhs.x) << info(index);
                ASSERT_EQ(expected[1], lhs.y) << info(index);
            }

            if constexpr (N == 3)
            {
                ASSERT_EQ(expected[0], lhs.x) << info(index);
                ASSERT_EQ(expected[1], lhs.y) << info(index);
                ASSERT_EQ(expected[2], lhs.z) << info(index);
            }

            if constexpr (N == 4)
            {
                ASSERT_EQ(expected[0], lhs.x) << info(index);
                ASSERT_EQ(expected[1], lhs.y) << info(index);
                ASSERT_EQ(expected[2], lhs.z) << info(index);
                ASSERT_EQ(expected[3], lhs.w) << info(index);
            }
        }

    };

    template<typename T, size_t N>
    struct write
    {
        stf::math::vec<T, N> initial;
        size_t index;
        T value;

        void verify(size_t const i) const
        {
            stf::math::vec<T, N> result = initial;
            result[index] = value;
            ASSERT_EQ(value, result[index]) << info(i);
        }

    };

    template<typename T, size_t N>
    struct add
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        stf::math::vec<T, N> expected;

        void verify(size_t const i) const
        {
            using vec_t = stf::math::vec<T, N>;
            ASSERT_EQ(expected, lhs + rhs) << info(i) << "Failed lhs + rhs";
            ASSERT_EQ(expected, rhs + lhs) << info(i) << "Failed rhs + lhs";
            ASSERT_EQ(expected, vec_t(lhs) += rhs) << info(i) << "Failed lhs += rhs";
            ASSERT_EQ(expected, vec_t(rhs) += lhs) << info(i) << "Failed lhs += rhs";
        }

    };

    template<typename T, size_t N>
    struct subtract
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        stf::math::vec<T, N> expected;

        void verify(size_t const i) const
        {
            using vec_t = stf::math::vec<T, N>;
            ASSERT_EQ(expected, lhs - rhs) << info(i) << "Failed lhs - rhs";
            ASSERT_EQ(-expected, rhs - lhs) << info(i) << "Failed rhs - lhs";
            ASSERT_EQ(expected, vec_t(lhs) -= rhs) << info(i) << "Failed lhs -= rhs";
            ASSERT_EQ(-expected, vec_t(rhs) -= lhs) << info(i) << "Failed rhs -= lhs";
        }

    };

    template<typename T, size_t N>
    struct scale
    {
        stf::math::vec<T, N> initial;
        T scalar;
        stf::math::vec<T, N> expected;

        void verify(size_t i) const
        {
            using vec_t = stf::math::vec<T, N>;
            ASSERT_EQ(expected, scalar * initial) << info(i) << "Failed scalar * initial";
            ASSERT_EQ(expected, initial * scalar) << info(i) << "Failed initial * scalar";
            ASSERT_EQ(expected, vec_t(initial) *= scalar) << info(i) << "Failed initial *= scalar";
        }

    };

    template<typename T, size_t N>
    struct dot
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        T expected;

        void verify(size_t const i) const
        {
            ASSERT_EQ(expected, stf::math::dot(lhs, rhs)) << info(i) << "Failed dot(lhs, rhs)";
            ASSERT_EQ(expected, stf::math::dot(rhs, lhs)) << info(i) << "Failed dot(rhs, lhs)";
            ASSERT_EQ(expected, lhs.dot(rhs)) << info(i) << "Failed lhs.dot(rhs)";
            ASSERT_EQ(expected, rhs.dot(lhs)) << info(i) << "Failed rhs.dot(lhs)";
        }
    };

    template<typename T, size_t N>
    struct length
    {
        stf::math::vec<T, N> initial;
        T expected;
    };

    template<typename T, size_t N>
    void verify(length<T, N> const& test)
    {
        ASSERT_EQ(test.expected, test.initial.length()) << "Failed initial.length()";
    }

    template<typename T, size_t N>
    struct normalize
    {
        stf::math::vec<T, N> initial;
        stf::math::vec<T, N> expected;
    };

    template<typename T, size_t N>
    void verify(normalize<T, N> const& test)
    {
        using vec_t = stf::math::vec<T, N>;
        ASSERT_EQ(test.expected, vec_t(test.initial).normalize()) << "Failed initial.normalize()";
        ASSERT_EQ(test.expected, test.initial.normalized()) << "Failed initial.normalized()";
    }

    template<typename T, typename U, size_t N>
    struct cast
    {
        stf::math::vec<T, N> initial;
    };

    template<typename T, typename U, size_t N>
    void verify(cast<T, U, N> const& test)
    {
        stf::math::vec<U, N> result = test.initial.template as<U>();
        for (size_t i = 0; i < N; ++i)
        {
            ASSERT_EQ(static_cast<U>(test.initial[i]), result[i]) << "Failed to cast properly";
        }
    }

    template<typename T, size_t N>
    struct negate
    {
        stf::math::vec<T, N> initial;
    };

    template<typename T, size_t N>
    void verify(negate<T, N> const& test)
    {
        stf::math::vec<T, N> result = -test.initial;
        for (size_t i = 0; i < N; ++i)
        {
            ASSERT_EQ(-test.initial[i], result[i]);
        }
    }

    template<typename T, size_t N>
    struct binary_op
    {
        stf::math::vec<T, N> lhs;
        stf::math::vec<T, N> rhs;
        stf::math::vec<T, N> expected;
    };

} // stf::scaffolding::math::vec