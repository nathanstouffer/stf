#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/tessellation.hpp>

namespace stf::alg::scaffolding::tessellation
{

    template<typename T>
    struct max_segment_length
    {
        geom::polyline2<T> const polyline;
        T const max_len;
        std::vector<math::vec2<T>> const expected;
    };

    template<typename T>
    void verify(max_segment_length<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::tessellate(test.polyline, test.max_len)) << "Failed to tessellate polyline";
    }

} // stf::alg::scaffolding::tessellation