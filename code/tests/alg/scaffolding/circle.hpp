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
        T radians;
        T degrees;
    };

    template<typename T>
    void verify(conversion<T> const& test)
    {
        ASSERT_FLOAT_EQ(test.degrees, degrees(test.radians)) << "Failed to convert radians to degrees";
        ASSERT_FLOAT_EQ(test.radians, radians(test.degrees)) << "Failed to convert degrees to radians";
    }

} // circle
} // scaffolding
} // alg
} // stf