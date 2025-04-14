#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/math/transform.hpp>

namespace stf::scaffolding::math::transform
{

    template<typename T>
    struct rotate2
    {
        math::vec<T, 2> initial;
        T delta_theta;
        math::vec<T, 2> expected;
    };

    template<typename T>
    void verify(rotate2<T> const& test)
    {
        ASSERT_EQ(test.expected, math::rotate(test.initial, test.delta_theta)) << "Failed rotate function";
        ASSERT_EQ(test.expected, math::rotate(test.delta_theta) * test.initial) << "Failed rotate matrix";
    }

    template<typename T>
    struct orbit2
    {
        math::vec<T, 2> initial;
        math::vec<T, 2> focus;
        T delta_theta;
        math::vec<T, 2> expected;
    };

    template<typename T>
    void verify(orbit2<T> const& test)
    {
        ASSERT_EQ(test.expected, math::orbit(test.initial, test.focus, test.delta_theta)) << "Failed orbit function";
    }

    template<typename T>
    struct rotate3
    {
        math::vec<T, 3> initial;
        math::vec<T, 3> axis;
        T delta_theta;
        math::vec<T, 3> expected;
    };

    template<typename T>
    void verify(rotate3<T> const& test)
    {
        using homogenized_t = math::vec<T, 4>;
        ASSERT_EQ(test.expected, math::rotate(test.initial, test.axis, test.delta_theta)) << "Failed rotate function";
        ASSERT_EQ(test.expected, (math::rotate(test.axis, test.delta_theta) * homogenized_t(test.initial, 1)).xyz) << "Failed rotate matrix";
    }

    template<typename T>
    struct orbit3
    {
        math::vec<T, 3> initial;
        math::vec<T, 3> focus;
        math::vec<T, 3> right;
        T delta_phi;
        T delta_theta;
        math::vec<T, 3> expected;
    };

    template<typename T>
    void verify(orbit3<T> const& test)
    {
        using homogenized_t = math::vec<T, 4>;
        ASSERT_EQ(test.expected, math::orbit(test.initial, test.focus, test.right, test.delta_phi, test.delta_theta)) << "Failed orbit function";
        ASSERT_EQ(test.expected, (math::orbit(test.focus, test.right, test.delta_phi, test.delta_theta) * homogenized_t(test.initial, 1)).xyz) << "Failed orbit matrix";
    }

} // stf::scaffolding::math::transform