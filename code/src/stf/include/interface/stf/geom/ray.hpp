#pragma once

#include "stf/math/vector.hpp"

/**
 * @file ray.hpp
 * @brief A file containing a templated ray class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief A ray class representing rays R^n
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct ray final
    {

        /**
         * @brief Type alias for vector type
         */
        using vec_t = math::vec<T, N>;

    public:

        /**
         * @brief The origin point of the ray
         */
        vec_t point;

        /**
         * @brief The direction of the ray
         */
        vec_t direction;

        /**
         * @brief Construct from a point and direction
         * @param [in] _point 
         * @param [in] _direction 
         */
        ray(vec_t const& _point, vec_t const& _direction) : point(_point), direction(_direction) {}

        /**
         * @brief Normalize the direction of a @ref ray
         * @return A reference to @p this
         */
        inline ray& normalize() { direction.normalize(); return *this; }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid ray specialization
     */
    template<typename T> struct ray<T, 0> { ray() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2D @ref ray
     * @tparam T Number type (eg float)
     */
    template<typename T> using ray2 = ray<T, 2>;

    /**
     * @brief Type alias for a 3D @ref ray
     * @tparam T Number type (eg float)
     */
    template<typename T> using ray3 = ray<T, 3>;

} // stf::geom