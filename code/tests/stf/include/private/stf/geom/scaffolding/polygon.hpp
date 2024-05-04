#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polygon.hpp>

namespace stf::geom::scaffolding::polygon
{

    template<typename T>
    struct is_convex
    {
        geom::polygon<T> const polygon;
        bool const convex;
    };

    template<typename T>
    void verify(is_convex<T> const& test)
    {
        ASSERT_EQ(test.convex, test.polygon.is_convex()) << "failed polygon.is_convex()";
    }

}