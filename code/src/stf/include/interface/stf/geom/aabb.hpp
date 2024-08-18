#pragma once

#include <cstring>

#include <limits>
#include <vector>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

/**
 * @file aabb.hpp
 * @brief A file containing a templated aabb class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief An aabb class representing subsets of R^n
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct aabb final
    {
    public:

        /**
         * @brief Type alias for vector type
         */
        using vec_t = math::vec<T, N>;

    public:

        /**
         * @brief The minimum of the @ref aabb
         */
        vec_t min;

        /**
         * @brief The maximum of the @ref aabb
         */
        vec_t max;

        /**
         * @brief Default constructor -- encompasses all of R^n
         */
        aabb() : aabb(vec_t(math::constants<T>::neg_inf), vec_t(math::constants<T>::pos_inf)) {}

        /**
         * @brief Construct from minimum and maximum points
         * @param [in] _min 
         * @param [in] _max 
         */
        aabb(vec_t const& _min, vec_t const& _max) : min(_min), max(_max) {}
        
        /**
         * @brief Construct from a minimum and a side length that is applied in all dimensinos
         * @param [in] _min 
         * @param [in] length 
         */
        aabb(vec_t const& _min, T const length) : aabb(_min, _min + vec_t(length)) {}

        /**
         * @brief Compute the @p i vertex of an @ref aabb
         * 
         * In 2 dimensions:
         * @verbatim
         2----3
         |    |
         |    |
         0----1 @endverbatim
         * 
         * In 3 dimensions:
         * @verbatim
           6----7
          /|   /|
         2----3 |
         | 4--|-5
         |/   |/
         0----1 @endverbatim
         * 
         * @param [in] i
         * @note @p index = 0 is the minimum
         * @note In 2D, @p index = 3 is the maximum
         * @note In 3D, @p index = 7 is the maximum
         * @return The 
         */
        vec_t vertex(size_t const i) const
        {
            vec_t vert = min;
            for (size_t j = 0; j < N; ++j)
            {
                if ((i & (1 << j)) != 0)
                {
                    vert[j] = max[j];
                }
            }
            return vert;
        }

        /**
         * @brief Compute an extremity of an @ref aabb in a given direction
         * @param [in] direction 
         * @return A vertex of @p this that is maximally extreme in @p direction
         */
        vec_t extremity(vec_t const& direction) const
        {
            vec_t extremity;
            for (size_t i = 0; i < N; ++i)
            {
                extremity[i] = (direction[i] > 0) ? max[i] : min[i];
            }
            return extremity;
        }

        /**
         * @brief Compute the diagonal of an @ref aabb
         * @return The diagonal vector of @p this
         */
        inline vec_t const diagonal() const { return max - min; }

        /**
         * @brief Compute the center of an @ref aabb
         * @return The center point of @p this
         */
        inline vec_t const center() const { return min + (math::constants<T>::half * diagonal()); }

        /**
         * @brief Scale an @ref aabb in place
         * @param [in] scalar 
         * @return A reference to @p this
         */
        aabb& scale(T const scalar) { min *= scalar; max *= scalar; return *this; }

        /**
         * @brief Scale an @ref aabb
         * @param [in] scalar 
         * @return @p this scaled by @p scalar
         */
        aabb scaled(T const scalar) const { return aabb(*this).scale(scalar); }

        /**
         * @brief Translate an @ref aabb in place
         * @param [in] delta 
         * @return A reference to @p this
         */
        aabb& translate(vec_t const& delta) { min += delta; max += delta; return *this; }

        /**
         * @brief Translate an @ref aabb
         * @param [in] delta 
         * @return @p this translated by @p delta
         */
        aabb translated(vec_t const& delta) const { return aabb(*this).translate(delta); }

        /**
         * @brief Fit a point to an @ref aabb in place
         * @param [in] x 
         * @return A reference to @p this
         */
        aabb& fit(vec_t const& x)
        {
            for (size_t i = 0; i < N; ++i)
            {
                min[i] = std::min(min[i], x[i]);
                max[i] = std::max(max[i], x[i]);
            }
            return *this;
        }

        /**
         * @brief Fit an @ref aabb to an @ref aabb in place
         * @param [in] rhs 
         * @return A reference to @p this
         */
        aabb& fit(aabb const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                min[i] = std::min(min[i], rhs.min[i]);
                max[i] = std::max(max[i], rhs.max[i]);
            }
            return *this;
        }

        /**
         * @brief Compute whether a point is contained in an @ref aabb
         * @param [in] x 
         * @return Whether or not @p x is contained in @p this
         */
        bool contains(vec_t const& x) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool contained = min[i] <= x[i] && x[i] <= max[i];
                if (!contained) { return false; }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute whether one @ref aabb contains another
         * @param [in] rhs
         * @return Whether or not @p rhs is contained in @p this
         */
        bool contains(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool contained = min[i] <= rhs.min[i] && rhs.max[i] <= max[i];
                if (!contained) { return false; }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute if two @ref aabb intersect
         * @param [in] rhs 
         * @return Whether or not @p this and @p rhs intersect
         */
        bool intersects(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool empty = rhs.max[i] < min[i] || max[i] < rhs.min[i];
                if (empty) { return false; }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute the volume of a @ref aabb
         * @return The volume of @p this
         */
        T volume() const
        {
            T const delta = diagonal();
            T measure = math::constants<T>::one;
            for (size_t i = 0; i < N; ++i)
            {
                measure *= (delta[i] < math::constants<T>::zero) ? delta[i] : math::constants<T>::zero;
            }
            return measure;
        }

        /**
         * @brief Compute the square of the distance from an aabb to a point
         * @param [in] point
         * @return The square of the distance from @p this to @p point
         */
        T dist_squared_to(vec_t const& point) const
        {
            if (contains(point))
            {
                return math::constants<T>::zero;
            }
            else
            {
                return math::dist_squared(point, math::clamp(point, min, max));
            }
        }

        /**
         * @brief Compute the distance from an aabb to a point
         * @param [in] point
         * @return The distance from @p this to @p point
         */
        T dist_to(vec_t const& point) const { return std::sqrt(dist_squared_to(point)); }

    public:

        /**
         * @brief Construct an @ref aabb that encompasses all of R^n
         * @return An @ref aabb that encompasses all of R^n
         */
        static aabb everything() { return aabb(); }

        /**
         * @brief Construct an @ref aabb that is the empty set
         * @return An @ref aabb that is the empty set
         */
        static aabb nothing() { return aabb(vec_t(math::constants<T>::pos_inf), vec_t(math::constants<T>::neg_inf)); }

        /**
         * @brief Construct an @ref aabb that minimally encompasses the unit cube in R^n
         * @return An @ref aabb that encompasses the unit cube in R^n
         */
        static aabb unit() { return aabb(vec_t(math::constants<T>::zero), vec_t(math::constants<T>::one)); }

        /**
         * @brief Construct an @ref aabb that minimally encompasses a set of points
         * @param [in] points 
         * @return An @ref aabb that minimally encompasses @p points
         */
        static aabb fit(std::vector<vec_t> const& points)
        {
            aabb box = aabb::nothing();
            for (vec_t const& point : points)
            {
                box.fit(point);
            }
            return box;
        }

        /**
         * @brief Compute the number of bytes allocated by @ref aabb
         * @return The byte count
         */
        inline static size_t byte_count() { return 2 * vec_t::byte_count(); }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid aabb specialization
     */
    template<typename T> struct aabb<T, 0> { aabb() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2D @ref aabb
     * @tparam T Number type (eg float) 
     */
    template<typename T> using aabb2 = aabb<T, 2>;

    /**
     * @brief Type alias for a 3D @ref aabb
     * @tparam T Number type (eg float)
     */
    template<typename T> using aabb3 = aabb<T, 3>;

    /**
     * @brief Fit two bounding boxes
     * @tparam T Number type (float)
     * @tparam N Dimension
     * @param [in] lhs 
     * @param [in] rhs 
     * @return A new bounding box that minimally encompasses @p lhs and @p rhs
     */
    template<typename T, size_t N>
    aabb<T, N> const fit(aabb<T, N> const& lhs, aabb<T, N> const& rhs)
    {
        return aabb<T, N>(lhs).fit(rhs);
    }

    /**
     * @brief Write the @ref aabb @p rhs to the std::ostream @p s
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in,out] s
     * @param [in] rhs
     * @return A reference to @p s
     */
    template <typename T, size_t N>
    inline std::ostream& operator<<(std::ostream& s, aabb<T, N> const& rhs)
    {
        s << "{ min: " << rhs.min << ", max: " << rhs.max << " }";
        return s;
    }

} // stf::geom