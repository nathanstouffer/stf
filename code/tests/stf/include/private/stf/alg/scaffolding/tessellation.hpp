#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/tessellation.hpp>

namespace stf::alg::scaffolding::tessellation
{

    template<typename T>
    struct polyline_via_length
    {
        geom::polyline2<T> const polyline;
        T const max_len;
        std::vector<math::vec2<T>> const expected;
    };

    template<typename T>
    void verify(polyline_via_length<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::tessellate_via_length(test.polyline, test.max_len)) << "Failed to tessellate polyline";
    }

} // stf::alg::scaffolding::tessellation