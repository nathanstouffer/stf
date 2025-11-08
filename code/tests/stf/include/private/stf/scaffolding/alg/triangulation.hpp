#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/triangulation.hpp>

namespace stf::alg::scaffolding::triangulation
{

    template<typename T>
    struct earclip_polygon
    {
        geom::polygon<T> polygon;
    };

    template<typename T>
    void verify(earclip_polygon<T> const& test)
    {
        std::vector<triangle<uint16_t>> triangles = alg::earclip<uint16_t, T>(test.polygon);
        T area = math::constants<T>::zero;
        for (triangle<uint16_t> const& tri : triangles)
        {
            math::vec2<T> const& a = test.polygon[tri.a];
            math::vec2<T> const& b = test.polygon[tri.b];
            math::vec2<T> const& c = test.polygon[tri.c];
            area += math::constants<T>::half * std::abs(math::cross(b - a, c - a));
        }
        ASSERT_EQ(test.polygon.area(), area) << "Failed to triangulate polygon";
    }

} // stf::alg::scaffolding::triangulation