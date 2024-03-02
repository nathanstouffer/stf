#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polyline.hpp>

namespace stf::geom::scaffolding::polyline
{

    template<typename T, size_t N>
    struct length
    {
        geom::polyline<T, N> const polyline;
        T const len;
    };

    template<typename T, size_t N>
    void verify(length<T, N> const& test)
    {
        ASSERT_EQ(test.len, test.polyline.length()) << "failed polyline.length()";
    }

}