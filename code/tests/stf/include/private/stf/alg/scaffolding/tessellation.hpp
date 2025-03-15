#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/tessellation.hpp>

namespace stf::alg::scaffolding::tessellation
{

    template<typename T>
    struct polyline_via_length
    {
        geom::polyline2<T> polyline;
        T max_len;
        bool loop;
        std::vector<math::vec2<T>> expected;
    };

    template<typename T>
    void verify(polyline_via_length<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::tessellate_via_length(test.polyline, test.max_len, test.loop)) << "Failed to tessellate polyline";
    }

} // stf::alg::scaffolding::tessellation