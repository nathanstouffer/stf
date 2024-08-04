#pragma once

#include <vector>

#include "stf/geom/polyline.hpp"
#include "stf/math/constants.hpp"

/**
 * @file tessellation.hpp
 * @brief A file containing functions that tessellate geometric primitives
 * @todo Write a polyline tessellation algorithm that adds vertices at all intersections with a grid
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
    std::vector<math::vec2<T>> tessellate_via_length(geom::polyline2<T> const& polyline, T const max_len, bool const loop)
    {
        std::vector<math::vec2<T>> vertices;
        if (polyline.is_empty()) { return vertices; }
        
        vertices.reserve(static_cast<size_t>(polyline.length() / max_len));
        for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all polyline edges, adding vertices
        {
            geom::segment2<T> edge = polyline.edge(i);
            vertices.push_back(edge.a);    // immediately push the first vertex in the segment

            T const length = edge.length();
            if (length > max_len)    // if necessary, add tessellated vertices
            {
                size_t count = static_cast<size_t>(std::ceil(length / max_len - math::constants<T>::one));  // the number of vertices we add to the interior of the segment
                T const delta_t = math::constants<T>::one / static_cast<T>(count + 1);
                for (size_t j = 1; j <= count; ++j)
                {
                    vertices.push_back(edge.interpolate(static_cast<T>(j) * delta_t));
                }
            }
        }

        if (loop)
        {

        }
        else
        {
            vertices.push_back(polyline.vertices().back());
        }

        return vertices;
    }

} // stf::alg