#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::cam::scaffolding::scamera
{

    template<typename T>
    struct direction_vectors
    {
        cam::scamera<T> const camera;
        math::vec3<T> const look;
        math::vec3<T> const up;
        math::vec3<T> const right;
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
        cam::scamera<T> const initial;
        math::vec3<T> const focus;
        T const delta_phi;
        T const delta_theta;
        cam::scamera<T> const expected;
    };

    template<typename T>
    void verify(orbit<T> const& test)
    {
        ASSERT_EQ(test.expected, cam::orbit(test.initial, test.focus, test.delta_phi, test.delta_theta)) << "Failed scamera orbit function";
    }

} // stf::cam::scaffolding::scamera