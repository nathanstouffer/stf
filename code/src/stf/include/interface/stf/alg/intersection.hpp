#pragma once

#include <optional>

#include "stf/geom/ray.hpp"
#include "stf/geom/hyperplane.hpp"

/**
 * @file intersection.hpp
 * @brief A file containing functions that report the (possibly empty) intersection of two geometric objects
 */

namespace stf::alg
{

    /**
     * @brief 
     * @tparam T Number type (eg float)
     * @param [in] 
     * @param [in] 
     * @return 
     */
    template<typename T>
    inline std::optional<math::vec3<T>> intersection(geom::ray3<T> const& beam, geom::plane<T> const& plane)
    {
        
    }

} // stf::alg