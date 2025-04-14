#pragma once

#include <gtest/gtest.h>

#include <stf/math/spherical.hpp>
#include <stf/stf.hpp>

namespace stf::scaffolding::math::spherical
{

    template<typename T>
    struct conversion
    {
        T radians;
        T degrees;
    };

    template<typename T>
    void verify(conversion<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.degrees, to_degrees(test.radians)) << "Failed to convert radians to degrees";
        ASSERT_FLOAT_EQ(test.radians, to_radians(test.degrees)) << "Failed to convert degrees to radians";
    }

    template<typename T>
    struct canonical_angle
    {
        T radians;
        T expected;
    };

    template<typename T>
    void verify(canonical_angle<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.expected, math::canonical_angle(test.radians)) << "Failed to compute canonical angle";
    }

    template<typename T>
    struct closest_equiv_angle
    {
        T phi;
        T theta;
        T expected;
    };

    template<typename T>
    void verify(closest_equiv_angle<T> const& test)
    {
        // NOTE: unfortunately, we had to relax floating point equality on this on a bit
        ASSERT_NEAR(test.expected, math::closest_equiv_angle(test.phi, test.theta), math::constants<T>::tol) << "Failed to compute closest equivalent angle";
    }

    template<typename T>
    struct counterclockwise_angle
    {
        vec2<T> u;
        vec2<T> v;
        T theta;
    };

    template<typename T>
    void verify(counterclockwise_angle<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.theta, math::counterclockwise_angle(test.u, test.v)) << "Failed to compute counterclockwise angle";
    }

    template<typename T>
    struct unit_vec2
    {
        T theta;
        math::vec<T, 2> expected;
    };

    template<typename T>
    void verify(unit_vec2<T> const& test)
    {
        ASSERT_EQ(test.expected, math::unit_vector(test.theta)) << "Failed to compute unit vector";
    }

    template<typename T>
    struct to_euclidean
    {
        T radius;
        T theta;
        T phi;
        math::vec<T, 3> expected;
    };

    template<typename T>
    void verify(to_euclidean<T> const& test)
    {
        ASSERT_EQ(test.expected, math::to_euclidean(test.radius, test.theta, test.phi)) << "Failed to compute euclidean coordinates";
    }

} // stf::scaffolding::math::spherical