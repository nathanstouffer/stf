#pragma once

#include <gtest/gtest.h>

#include <stf/math/spherical.hpp>
#include <stf/types.hpp>

namespace stf::math::scaffolding::spherical
{

    template<typename T>
    struct conversion
    {
        T const radians;
        T const degrees;
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
        T const radians;
        T const expected;
    };

    template<typename T>
    void verify(canonical_angle<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.expected, math::canonical_angle(test.radians)) << "Failed to compute canonical angle";
    }

    template<typename T>
    struct closest_equiv_angle
    {
        T const phi;
        T const theta;
        T const expected;
    };

    template<typename T>
    void verify(closest_equiv_angle<T> const& test)
    {
        // NOTE: unfortunately, we had to relax floating point equality on this on a bit
        ASSERT_NEAR(test.expected, math::closest_equiv_angle(test.phi, test.theta), stff::constants::tol) << "Failed to compute closest equivalent angle";
    }

    template<typename T>
    struct unit_vec2
    {
        T const theta;
        math::vec<T, 2> const expected;
    };

    template<typename T>
    void verify(unit_vec2<T> const& test)
    {
        ASSERT_EQ(test.expected, math::unit_vector(test.theta)) << "Failed to compute unit vector";
    }

} // stf::math::scaffolding::spherical