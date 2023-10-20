#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/circle.hpp>

namespace stf {
namespace alg {
namespace scaffolding {
namespace circle {

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
    struct canonical
    {
        T const radians;
        T const expected;
    };

    template<typename T>
    void verify(canonical<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.expected, canonical_angle(test.radians)) << "Failed to compute canonical angle";
    }

} // circle
} // scaffolding
} // alg
} // stf