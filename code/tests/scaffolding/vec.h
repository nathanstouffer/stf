#pragma once

#include <gtest/gtest.h>

#include <stf/math/vector.h>

namespace stf {
namespace scaffolding {
namespace vec {

    template<typename T, size_t N>
    struct equality
    {
        stf::math::vec<T, N> const lhs;
        stf::math::vec<T, N> const rhs;
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
    struct read
    {
        stf::math::vec<T, N> const lhs;
        T const expected[N];
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
        stf::math::vec<T, N> const initial;
        size_t const index;
        T const value;
    };

    template<typename T, size_t N>
    void verify(write<T, N> const& test)
    {
        stf::math::vec<T, N> result = test.initial;
        result[test.index] = test.value;
        ASSERT_EQ(result[test.index], test.value);
    }

    template<typename T, size_t N>
    struct negate
    {
        stf::math::vec<T, N> const initial;
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
        stf::math::vec<T, N> const lhs;
        stf::math::vec<T, N> const rhs;
        stf::math::vec<T, N> const expected;
    };

} // vec
} // scaffolding
} // stf