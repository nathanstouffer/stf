#pragma once

#include "stf/math/vector.hpp"

/**
 * @file sphere.hpp
 * @brief A file containing a templated sphere class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief A class representing a sphere in R^n
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct sphere final
    {

        /**
         * @brief Type alias for vector type
         */
        using vec_t = math::vec<T, N>;

    public:

        /**
         * @brief The center of the sphere
         */
        vec_t center;

        /**
         * @brief The radius of the sphere
         */
        T radius;

        /**
         * @brief Construct from a center point and radius
         * @param [in] _center
         * @param [in] _radius
         */
        sphere(vec_t const& _center, T const _radius) : center(_center), radius(_radius) {}

        /**
         * @brief Compute whether or not the sphere encloses a point
         * @param [in] query
         * @return Whether or not @p this encloses @p query
         */
        bool const encloses(vec_t const& query) const
        {
            vec_t delta = query - center;
            return delta.length_squared() <= radius * radius;
        }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid sphere specialization
     */
    template<typename T> struct sphere<T, 0> { sphere() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a @ref sphere in 2 dimensions -- a circle
     * @tparam T Number type (eg float)
     */
    template<typename T> using circle = sphere<T, 2>;

    /**
     * @brief Type alias for a 2D @ref sphere
     * @tparam T Number type (eg float)
     */
    template<typename T> using sphere2 = sphere<T, 2>;

    /**
     * @brief Type alias for a 3D @ref ray
     * @tparam T Number type (eg float)
     */
    template<typename T> using sphere3 = ray<T, 3>;

} // stf::geom