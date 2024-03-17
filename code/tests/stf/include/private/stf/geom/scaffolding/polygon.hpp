#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polygon.hpp>

namespace stf::geom::scaffolding::polygon
{

    template<typename T>
    struct something
    {
        geom::polygon<T> const polygon;
        //T const len;
    };

    template<typename T>
    void verify(something<T> const& test)
    {
        //ASSERT_EQ(test.len, test.polyline.length()) << "failed polyline.length()";
    }

}