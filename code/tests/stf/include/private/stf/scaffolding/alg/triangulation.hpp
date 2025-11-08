#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/triangulation.hpp>

namespace stf::scaffolding::alg::triangulation
{

    template<typename T>
    struct earclip_polygon
    {
        geom::polygon<T> polygon;

        void verify(size_t const i) const
        {
            std::vector<stf::alg::triangle<uint16_t>> triangles = stf::alg::earclip<uint16_t, T>(polygon);
            T area = math::constants<T>::zero;
            for (stf::alg::triangle<uint16_t> const& tri : triangles)
            {
                math::vec2<T> const& a = polygon[tri.a];
                math::vec2<T> const& b = polygon[tri.b];
                math::vec2<T> const& c = polygon[tri.c];
                area += math::constants<T>::half * std::abs(math::cross(b - a, c - a));
            }
            ASSERT_EQ(polygon.area(), area) << info(i) << "Failed to triangulate polygon";
        }
    };

} // stf::alg::scaffolding::triangulation