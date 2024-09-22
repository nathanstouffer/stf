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

        /**
         * @brief Compute the square of the distance between a ray and a vector
         * @param [in] query
         * @return The square of the distance between @p this and @p point
         */
        T const dist_squared(vec_t const& query) const
        {
            vec_t unit_dir = direction.normalized();
            T scalar = (query - point) * unit_dir;
            T t = std::max(scalar, math::constants<T>::zero);
            vec_t proj = point + t * unit_dir;
            return (query - proj).length_squared();
        }

        /**
         * @brief Compute the distance between a ray and a vector
         * @param [in] point
         * @return The distance between @p this and @p point
         */
        inline T const dist(vec_t const& point) const { return std::sqrt(dist_squared(point)); }

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

    /**
     * @brief Compute the square of the distance between a ray and a vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] beam
     * @param [in] point
     * @return The square of the distance between @p beam and @p point
     */
    template<typename T, size_t N>
    inline T const dist_squared(ray<T, N> const& beam, math::vec<T, N> const& point)
    {
        return beam.dist_squared(point);
    }

    /**
     * @brief Compute the square of the distance between a vector and a ray
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] point
     * @param [in] beam
     * @return The square of the distance between @p point and @p seg
     */
    template<typename T, size_t N>
    inline T const dist_squared(math::vec<T, N> const& point, ray<T, N> const& beam)
    {
        return dist_squared(beam, point);
    }

    /**
     * @brief Compute the distance between a ray and a vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] beam
     * @param [in] point
     * @return The distance between @p beam and @p point
     */
    template<typename T, size_t N>
    inline T const dist(ray<T, N> const& beam, math::vec<T, N> const& point)
    {
        return beam.dist(point);
    }

    /**
     * @brief Compute the distance between a vector and a ray
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] beam
     * @param [in] point
     * @return The distance between @p point and @p beam
     */
    template<typename T, size_t N>
    inline T const dist(math::vec<T, N> const& point, ray<T, N> const& beam)
    {
        return std::sqrt(dist_squared(point, beam));
    }

} // stf::geom