#pragma once

#include <vector>

#include "stf/geom/polygon.hpp"

/**
 * @file triangulation.hpp
 * @brief A file containing functions that triangulate polygons
 */

namespace stf::alg
{

    template<typename T>
    struct triangle
    {
        T a;
        T b;
        T c;
    };


    template<typename T, typename U>
    std::vector<triangle<T>> earclip(geom::polygon<U> const& polygon);

}

namespace stf::alg
{

    template<typename T, typename U>
    std::vector<triangle<T>> earclip(geom::polygon<U> const& polygon)
    {
        return { { 0, 1, 2 } };
    }

}