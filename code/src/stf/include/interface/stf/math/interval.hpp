#pragma once

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"

/**
 * @file interval.hpp
 * @brief A file containing a templated interval class along with associated functions
 */

namespace stf::math
{

    /**
     * @brief An interval class representing a connected component of the real line
     * @tparam T Number type (eg float)
     */
    template<typename T>
    struct interval final
    {

        /**
         * @brief The infimum of the @ref interval
         */
        T a;

        /**
         * @brief The supremum of the @ref interval
         */
        T b;

        /**
         * @brief Default constructor for an interval: @ref a = @ref b = 0
         */
        interval() : a(constants<T>::zero), b(constants<T>::zero) {}

        /**
         * @brief Explicit constructor for an @ref interval
         * @param [in] _a 
         * @param [in] _b 
         */
        interval(T const _a, T const _b) : a(_a), b(_b) {}

        /**
         * @brief Compute whether two @ref intervals are equal
         * @param [in] rhs 
         * @return Returns whether @p this equals @p rhs
         */
        inline bool operator==(interval const& rhs) const { return a == rhs.a && b == rhs.b; }

        /**
         * @brief Computes whether or not the @ref interval is empty
         * @param [in] type Specifies whether the boundary of the interval is open or closed
         * @return Whether or not the interval is empty
         */
        inline bool is_empty(boundary_types type)
        {
            switch (type)
            {
                case boundary_types::CLOSED: return a > b; break;
                case boundary_types::OPEN: return a >= b; break;
                default: return false;
            }
        }

        /**
         * @brief Compute if an @ref interval contains a point
         * @param [in] x Query point
         * @param [in] type Specifies whether the boundary of the interval is open or closed
         * @return Whether or not @p this contains the value @p x
         */
        inline bool contains(T const x, boundary_types const type) const { return contains(a, b, x, type); }

        /**
         * @brief Compute whether or not one @ref interval contains a query @ref interval
         * @param [in] rhs Query interval 
         * @return Whether or not @p this entirely contains @p rhs
         */
        inline bool contains(interval const& rhs) const { return a <= rhs.a && rhs.b <= b; }

        /**
         * @brief Compute if two @ref intervals intersect
         * @param [in] rhs 
         * @return Whether or not @p this and @p rhs intersect
         */
        inline bool intersects(interval const& rhs) const { return !(rhs.b < a || b < rhs.a); }

        /**
         * @brief Compute whether or not a query point is contained in an @ref interval
         * @param [in] a Infimum of the interval
         * @param [in] b Supremum of the intervale
         * @param [in] x Query point
         * @param [in] type Specifies whether the boundary of the interval is open or closed
         * @return Whether or not @p x is contained in the interval formed by @p and @b
         */
        static inline bool contains(T const a, T const b, T const x, boundary_types const type)
        {
            switch (type)
            {
                case boundary_types::CLOSED: return a <= x && x <= b; break;
                case boundary_types::OPEN: return a < x && x < b; break;
                default: return false;
            };
        }

    };

} // stf::math