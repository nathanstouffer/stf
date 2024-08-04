#pragma once

#include <vector>

#include "stf/geom/polyline.hpp"

/**
 * @file tessellation.hpp
 * @brief A file containing functions that tessellate geometric primitives
 */

namespace stf::alg
{

    /**
     * @brief Tessellate a polyline adding vertices so that no segment is longer than a specified length
     * @tparam T Number type (eg float)
     * @param [in] polyline The polyline to be tessellated
     * @param [in] max_len The maximum segment length allowed in the returned sequence of vertices
     * @return A std::vector of the tessellated vertices
     */
    template<typename T>
    std::vector<math::vec2<T>> tessellate(geom::polyline2<T> const& polyline, T const max_len)
    {
        std::vector<math::vec2<T>> vertices;
        if (polyline.is_empty()) { return vertices; }
        
        vertices.reserve(static_cast<size_t>(polyline.length() / max_len));
        vertices.push_back(polyline.vertices().front());
        for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all polyline segments
        {
            geom::segment2<T> edge = polyline.edge(i);
        }
    }

} // stf::alg