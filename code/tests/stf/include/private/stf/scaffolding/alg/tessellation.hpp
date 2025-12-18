#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/tessellation.hpp>

namespace stf::scaffolding::alg::tessellation
{

template <typename T>
struct polyline_via_length
{
    stf::geom::polyline2<T> polyline;
    T max_len;
    bool loop;
    std::vector<stf::math::vec2<T>> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::alg::tessellate_via_length(polyline, max_len, loop))
            << info(i) << "Failed to tessellate polyline";
    }
};

} // namespace stf::scaffolding::alg::tessellation