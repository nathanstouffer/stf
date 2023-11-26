#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/spherical.hpp>

namespace stf {
namespace alg {
namespace scaffolding {
namespace spherical {

    template<typename T>
    struct conversion
    {
        T const radians;
        T const degrees;
    };

    template<typename T>
    void verify(conversion<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.degrees, degrees(test.radians)) << "Failed to convert radians to degrees";
        ASSERT_FLOAT_EQ(test.radians, radians(test.degrees)) << "Failed to convert degrees to radians";
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
        ASSERT_FLOAT_EQ(test.expected, alg::canonical_angle(test.radians)) << "Failed to compute canonical angle";
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
        ASSERT_NEAR(test.expected, alg::closest_equiv_angle(test.phi, test.theta), stff::constants::tol) << "Failed to compute closest equivalent angle";
    }

} // circle
} // scaffolding
} // alg
} // stf