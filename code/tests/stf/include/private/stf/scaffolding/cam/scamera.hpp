#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::scaffolding::cam::scamera
{

    template<typename T>
    struct direction_vectors
    {
        cam::scamera<T> camera;
        math::vec3<T> look;
        math::vec3<T> up;
        math::vec3<T> right;
    };

    template<typename T>
    void verify(direction_vectors<T> const& test)
    {
        ASSERT_EQ(test.look, test.camera.look()) << "Failed to compute look vector";
        ASSERT_EQ(test.up, test.camera.up()) << "Failed to compute up vector";
        ASSERT_EQ(test.right, test.camera.right()) << "Failed to compute right vector";
    }

    template<typename T>
    struct orbit
    {
        cam::scamera<T> initial;
        math::vec3<T> focus;
        T delta_phi;
        T delta_theta;
        cam::scamera<T> expected;
    };

    template<typename T>
    void verify(orbit<T> const& test)
    {
        ASSERT_EQ(test.expected, cam::orbit(test.initial, test.focus, test.delta_phi, test.delta_theta)) << "Failed scamera orbit function";
    }

} // stf::scaffolding::cam::scamera