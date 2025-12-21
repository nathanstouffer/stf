#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::scaffolding::cam::scamera
{

template <typename T>
struct direction_vectors
{
    stf::cam::scamera<T> camera;
    stf::math::vec3<T> look;
    stf::math::vec3<T> up;
    stf::math::vec3<T> right;

    void verify(size_t const i) const
    {
        ASSERT_EQ(look, camera.look()) << info(i) << "Failed to compute look vector";
        ASSERT_EQ(up, camera.up()) << info(i) << "Failed to compute up vector";
        ASSERT_EQ(right, camera.right()) << info(i) << "Failed to compute right vector";
    }
};

template <typename T>
struct lerp
{
    stf::cam::scamera<T> lhs;
    stf::cam::scamera<T> rhs;
    T t;
    stf::cam::scamera<T> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::cam::lerp(lhs, rhs, t)) << info(i) << "Failed scamera lerp function";
    }
};

template <typename T>
struct orbit
{
    stf::cam::scamera<T> initial;
    stf::math::vec3<T> focus;
    T delta_phi;
    T delta_theta;
    stf::cam::scamera<T> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::cam::orbit(initial, focus, delta_phi, delta_theta))
            << info(i) << "Failed scamera orbit function";
    }
};

} // namespace stf::scaffolding::cam::scamera