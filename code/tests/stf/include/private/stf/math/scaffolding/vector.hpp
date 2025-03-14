#pragma once

#include <gtest/gtest.h>

#include <stf/math/vector.hpp>

namespace stf::math::scaffolding::vec
{

    template<typename T, size_t N>
    struct equality
    {
        math::vec<T, N> lhs;
        math::vec<T, N> rhs;
        bool equal;
    };

    template<typename T, size_t N>
    void verify(equality<T, N> const& test)
    {
        if (test.equal)
        {
            ASSERT_EQ(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs != test.rhs) << "failed negative assertion";
            ASSERT_TRUE(math::equ(test.lhs, test.rhs, T(0))) << "failed exact positive assertion";
            ASSERT_FALSE(math::neq(test.lhs, test.rhs, T(0))) << "failed exact negative assertion";
        }
        else
        {
            ASSERT_NE(test.lhs, test.rhs) << "failed positive assertion";
            ASSERT_FALSE(test.lhs == test.rhs) << "failed negative assertion";
            ASSERT_TRUE(math::neq(test.lhs, test.rhs, T(0))) << "failed exact positive assertion";
            ASSERT_FALSE(math::equ(test.lhs, test.rhs, T(0))) << "failed exact negative assertion";
        }
    }

    template<typename T, size_t N>
    struct read
    {
        math::vec<T, N> lhs;
        T expected[N];
    };

    template<typename T, size_t N>
    void verify(read<T, N> const& test)
    {
        for (size_t i = 0; i < N; ++i)
        {
            ASSERT_EQ(test.lhs[i], test.expected[i]);
        }
    }

    template<typename T>
    void verify(read<T, 2> const& test)
    {
        // call generalized template
        verify<T, 2>(test);
        ASSERT_EQ(test.lhs.x, test.expected[0]);
        ASSERT_EQ(test.lhs.y, test.expected[1]);
    }

    template<typename T>
    void verify(read<T, 3> const& test)
    {
        // call generalized template
        verify<T, 3>(test);
        ASSERT_EQ(test.lhs.x, test.expected[0]);
        ASSERT_EQ(test.lhs.y, test.expected[1]);
        ASSERT_EQ(test.lhs.z, test.expected[2]);
    }

    template<typename T>
    void verify(read<T, 4> const& test)
    {
        // call generalized template
        verify<T, 4>(test);
        ASSERT_EQ(test.lhs.x, test.expected[0]);
        ASSERT_EQ(test.lhs.y, test.expected[1]);
        ASSERT_EQ(test.lhs.z, test.expected[2]);
        ASSERT_EQ(test.lhs.w, test.expected[3]);
    }

    template<typename T, size_t N>
    struct write
    {
        math::vec<T, N> initial;
        size_t index;
        T value;
    };

    template<typename T, size_t N>
    void verify(write<T, N> const& test)
    {
        math::vec<T, N> result = test.initial;
        result[test.index] = test.value;
        ASSERT_EQ(result[test.index], test.value);
    }

    template<typename T, size_t N>
    struct add
    {
        math::vec<T, N> lhs;
        math::vec<T, N> rhs;
        math::vec<T, N> expected;
    };

    template<typename T, size_t N>
    void verify(add<T, N> const& test)
    {
        using vec_t = math::vec<T, N>;
        ASSERT_EQ(test.expected, test.lhs + test.rhs) << "Failed lhs + rhs";
        ASSERT_EQ(test.expected, test.rhs + test.lhs) << "Failed rhs + lhs";
        ASSERT_EQ(test.expected, vec_t(test.lhs) += test.rhs) << "Failed lhs += rhs";
        ASSERT_EQ(test.expected, vec_t(test.rhs) += test.lhs) << "Failed lhs += rhs";
    }

    template<typename T, size_t N>
    struct subtract
    {
        math::vec<T, N> lhs;
        math::vec<T, N> rhs;
        math::vec<T, N> expected;
    };

    template<typename T, size_t N>
    void verify(subtract<T, N> const& test)
    {
        using vec_t = math::vec<T, N>;
        ASSERT_EQ(test.expected, test.lhs - test.rhs) << "Failed lhs - rhs";
        ASSERT_EQ(-test.expected, test.rhs - test.lhs) << "Failed rhs - lhs";
        ASSERT_EQ(test.expected, vec_t(test.lhs) -= test.rhs) << "Failed lhs -= rhs";
        ASSERT_EQ(-test.expected, vec_t(test.rhs) -= test.lhs) << "Failed rhs -= lhs";
    }

    template<typename T, size_t N>
    struct scale
    {
        math::vec<T, N> initial;
        T scalar;
        math::vec<T, N> expected;
    };

    template<typename T, size_t N>
    void verify(scale<T, N> const& test)
    {
        using vec_t = math::vec<T, N>;
        ASSERT_EQ(test.expected, test.scalar * test.initial) << "Failed scalar * initial";
        ASSERT_EQ(test.expected, test.initial * test.scalar) << "Failed initial * scalar";
        ASSERT_EQ(test.expected, vec_t(test.initial) *= test.scalar) << "Failed initial *= scalar";
    }

    template<typename T, size_t N>
    struct dot
    {
        math::vec<T, N> lhs;
        math::vec<T, N> rhs;
        T expected;
    };

    template<typename T, size_t N>
    void verify(dot<T, N> const& test)
    {
        ASSERT_EQ(test.expected, math::dot(test.lhs, test.rhs)) << "Failed dot(lhs, rhs)";
        ASSERT_EQ(test.expected, math::dot(test.rhs, test.lhs)) << "Failed dot(rhs, lhs)";
        ASSERT_EQ(test.expected, test.lhs.dot(test.rhs)) << "Failed lhs.dot(rhs)";
        ASSERT_EQ(test.expected, test.rhs.dot(test.lhs)) << "Failed rhs.dot(lhs)";
    }

    template<typename T, size_t N>
    struct length
    {
        math::vec<T, N> initial;
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
        math::vec<T, N> initial;
        math::vec<T, N> expected;
    };

    template<typename T, size_t N>
    void verify(normalize<T, N> const& test)
    {
        using vec_t = math::vec<T, N>;
        ASSERT_EQ(test.expected, vec_t(test.initial).normalize()) << "Failed initial.normalize()";
        ASSERT_EQ(test.expected, test.initial.normalized()) << "Failed initial.normalized()";
    }

    template<typename T, typename U, size_t N>
    struct cast
    {
        math::vec<T, N> initial;
    };

    template<typename T, typename U, size_t N>
    void verify(cast<T, U, N> const& test)
    {
        math::vec<U, N> result = test.initial.template as<U>();
        for (size_t i = 0; i < N; ++i)
        {
            ASSERT_EQ(static_cast<U>(test.initial[i]), result[i]) << "Failed to cast properly";
        }
    }

    template<typename T, size_t N>
    struct negate
    {
        math::vec<T, N> initial;
    };

    template<typename T, size_t N>
    void verify(negate<T, N> const& test)
    {
        math::vec<T, N> result = -test.initial;
        for (size_t i = 0; i < N; ++i)
        {
            ASSERT_EQ(-test.initial[i], result[i]);
        }
    }

    template<typename T, size_t N>
    struct binary_op
    {
        math::vec<T, N> lhs;
        math::vec<T, N> rhs;
        math::vec<T, N> expected;
    };

} // stf::math::scaffolding::vec