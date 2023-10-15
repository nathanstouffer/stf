#pragma once

#include <gtest/gtest.h>

#include <stf/types.hpp>
#include <stf/alg/transform.hpp>

namespace stf {
namespace alg {
namespace scaffolding {
namespace transform {

    template<typename T>
    struct rotate3
    {
        math::vec<T, 3> const initial;
        math::vec<T, 3> const axis;
        T const delta_theta;
        math::vec<T, 3> const expected;
    };

    template<typename T>
    void verify(rotate3<T> const& test)
    {
        using homogenized_t = math::vec<T, 4>;
        ASSERT_EQ(test.expected, alg::rotate(test.initial, test.axis, test.delta_theta)) << "Failed rotate function";
        ASSERT_EQ(test.expected, (math::rotate(test.axis, test.delta_theta) * homogenized_t(test.initial, 1)).xyz) << "Failed rotate matrix";
    }

    template<typename T>
    struct orbit3
    {
        math::vec<T, 3> const initial;
        math::vec<T, 3> const focus;
        math::vec<T, 3> const right;
        T const delta_phi;
        T const delta_theta;
        math::vec<T, 3> const expected;
    };

    template<typename T>
    void verify(orbit3<T> const& test)
    {
        using homogenized_t = math::vec<T, 4>;
        ASSERT_EQ(test.expected, alg::orbit(test.initial, test.focus, test.right, test.delta_phi, test.delta_theta)) << "Failed orbit function";
        ASSERT_EQ(test.expected, (math::orbit(test.focus, test.right, test.delta_phi, test.delta_theta) * homogenized_t(test.initial, 1)).xyz) << "Failed orbit matrix";
    }

} // transform
} // scaffolding
} // alg
} // stf