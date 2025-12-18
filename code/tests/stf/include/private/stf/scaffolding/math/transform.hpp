#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/math/transform.hpp>

namespace stf::scaffolding::math::transform
{

template <typename T>
struct rotate2
{
    stf::math::vec<T, 2> initial;
    T delta_theta;
    stf::math::vec<T, 2> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::rotate(initial, delta_theta))
            << info(i) << "Failed rotate function";
        ASSERT_EQ(expected, stf::math::rotate(delta_theta) * initial)
            << info(i) << "Failed rotate matrix";
    }
};

template <typename T>
struct orbit2
{
    stf::math::vec<T, 2> initial;
    stf::math::vec<T, 2> focus;
    T delta_theta;
    stf::math::vec<T, 2> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::orbit(initial, focus, delta_theta))
            << info(i) << "Failed orbit function";
    }
};

template <typename T>
struct rotate3
{
    stf::math::vec<T, 3> initial;
    stf::math::vec<T, 3> axis;
    T delta_theta;
    stf::math::vec<T, 3> expected;

    void verify(size_t const i) const
    {
        using homogenized_t = stf::math::vec<T, 4>;
        ASSERT_EQ(expected, stf::math::rotate(initial, axis, delta_theta))
            << info(i) << "Failed rotate function";
        ASSERT_EQ(expected, (stf::math::rotate(axis, delta_theta) * homogenized_t(initial, 1)).xyz)
            << info(i) << "Failed rotate matrix";
    }
};

template <typename T>
struct orbit3
{
    stf::math::vec<T, 3> initial;
    stf::math::vec<T, 3> focus;
    stf::math::vec<T, 3> right;
    T delta_phi;
    T delta_theta;
    stf::math::vec<T, 3> expected;

    void verify(size_t const i) const
    {
        using homogenized_t = stf::math::vec<T, 4>;
        ASSERT_EQ(expected, stf::math::orbit(initial, focus, right, delta_phi, delta_theta))
            << info(i) << "Failed orbit function";
        ASSERT_EQ(expected, (stf::math::orbit(focus, right, delta_phi, delta_theta) *
                             homogenized_t(initial, 1))
                                .xyz)
            << info(i) << "Failed orbit matrix";
    }
};

} // namespace stf::scaffolding::math::transform