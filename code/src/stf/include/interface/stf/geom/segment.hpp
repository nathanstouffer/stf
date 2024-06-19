#pragma once

#include <algorithm>

#include "stf/geom/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"
#include "stf/math/vector.hpp"

/**
 * @file segment.hpp
 * @brief A file containing a templated segment class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief A class to represent straight-line segments in R^n
     * @tparam T Number type (float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct segment final
    {

        /**
         * @brief Type alias for vector type
         */
        using vec_t = math::vec<T, N>;

        /**
         * @brief Type alias for aabb type
         */
        using aabb_t = geom::aabb<T, N>;

    public:

        /**
         * @brief The first point of the segment
         */
        vec_t a;

        /**
         * @brief The second point of the segment
         */
        vec_t b;

        /**
         * @brief Default constructor -- both endpoints are the origin
         */
        segment() : segment(vec_t(math::constants<T>::zero), vec_t(math::constants<T>::zero)) {}

        /**
         * @brief Construct from two points
         * @param [in] _a 
         * @param [in] _b 
         */
        segment(vec_t const& _a, vec_t const& _b) : a(_a), b(_b) {}

        /**
         * @brief Compute the length of a @ref segment
         * @return The length of @p this
         */
        inline T length() const { return (b - a).length(); }

        /**
         * @brief Compute the slope of a @ref segment
         * @return The slope of @p this
         */
        inline T slope() const { vec_t diff = delta(); return diff.y / diff.x; }

        /**
         * @brief Compute the delta between the second and first point of the segment
         * @return The delta between @p b and @p a
         */
        inline vec_t delta() const { return b - a; }

        /**
         * @brief Compute the (normalized) direction of the segment
         * @return The normalized direction from @p a to @p b
         */
        inline vec_t direction() const { return delta().normalize(); }

        /**
         * @brief Compute the interval of space occupied by a given dimension
         * @param [in] i Dimension to compute the interval 
         * @return The interval of R that is occupied in dimension @p i
         */
        inline math::interval<T> interval(size_t i) const { return math::interval<T>(std::min(a[i], b[i]), std::max(a[i], b[i])); }

        /**
         * @brief Compute an @ref aabb that minimally encompasses the segment
         * @return The bounding box
         */
        inline aabb_t aabb() const
        {
            aabb_t box = aabb_t::nothing();
            box.fit(a);
            box.fit(b);
            return box;
        }

        /**
         * @brief Compute the distance from the segment to a query point
         * @param [in] p 
         * @return The distance from @p this to @p p
         */
        inline T distance_to(vec_t const& p) const
        {
            vec_t diff = delta();
            T scalar = ((p - a) * diff) / (diff * diff);
            T t = std::clamp(scalar, math::constants<T>::zero, math::constants<T>::one);
            vec_t proj = a + t * diff;
            return (p - proj).length();
        }

        /**
         * @brief Interpolate along the semgent
         * @param [in] t 
         * @note Clamped to the endpoints outside of [0, 1]
         * @return The interpolated point
         */
        vec_t interpolate(T const t) const
        {
            T s = std::clamp(t, math::constants<T>::zero, math::constants<T>::one);
            return (math::constants<T>::one - s) * a + s * b;
        }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid segment specialization
     */
    template<typename T> struct segment<T, 0> { segment() = delete; };
    /**
     * @brief Delete invalid segment specialization
     */
    template<typename T> struct segment<T, 1> { segment() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2D @ref segment
     * @tparam T Number type (eg float)
     */
    template<typename T> using segment2 = segment<T, 2>;

    /**
     * @brief Type alias for a 3D @ref segment
     * @tparam T Number type (eg float)
     */
    template<typename T> using segment3 = segment<T, 3>;

} // stf::geom