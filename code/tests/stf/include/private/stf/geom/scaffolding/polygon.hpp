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

    template<typename T>
    struct signed_area
    {
        geom::polygon<T> const polygon;
        T const area;
    };

    template<typename T>
    void verify(signed_area<T> const& test)
    {
        ASSERT_EQ(test.area, test.polygon.signed_area()) << "failed polygon.signed_area()";
        ASSERT_EQ(std::abs(test.area), test.polygon.area()) << "failed polygon.area()";
    }

    template<typename T>
    struct contains
    {
        geom::polygon<T> const polygon;
        math::vec2<T> const query;
        boundary const boundary_type;
        bool const contained;
    };

    template<typename T>
    void verify(contains<T> const& test)
    {
        ASSERT_EQ(test.contained, test.polygon.contains(test.query, test.boundary_type)) << "failed polygon.contains()";
    }

}