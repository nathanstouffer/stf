#pragma once

#include <optional>

#include "stf/alg/intersects.hpp"
#include "stf/geom/ray.hpp"
#include "stf/geom/hyperplane.hpp"

/**
 * @file intersect.hpp
 * @brief A file containing functions that report the (possibly empty) intersection of two geometric objects
 */

namespace stf::alg
{

    /**
     * @brief Compute the intersection of a ray and a plane
     * @tparam T Number type (eg float)
     * @param [in] ray
     * @param [in] plane
     * @note If @p ray is a subset of @p plane, the origin of @p ray will be returned
     * @return The (possibly empty) intersection of @p ray and @p plane
     */
    template<typename T>
    std::optional<math::vec3<T>> intersect(geom::ray3<T> const& ray, geom::plane<T> const& plane)
    {
        if (intersects(ray, plane))
        {
            if (plane.contains(ray.point))
            {
                return ray.point;
            }
            else
            {
                T const dist = plane.dist(ray.point);
                T const dot = math::dot(plane.normal(), ray.direction);
                T const scalar = dist / std::abs(dot);
                return ray.point + scalar * ray.direction;
            }
        }
        else
        {
            return std::nullopt;
        }
    }

    /**
     * @brief Compute the intersection of a plane and a ray
     * @tparam T Number type (eg float)
     * @param [in] plane
     * @param [in] ray
     * @note If @p ray is a subset of @p plane, the origin of @p ray will be returned
     * @return The (possibly empty) intersection of @p plane and @p ray
     */
    template<typename T>
    inline std::optional<math::vec3<T>> intersect(geom::plane<T> const& plane, geom::ray3<T> const& ray)
    {
        return intersect(ray, plane);
    }

} // stf::alg