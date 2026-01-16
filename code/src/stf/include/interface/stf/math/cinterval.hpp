#ifndef STF_MATH_CINTERVAL_HPP_HEADER_GUARD
#define STF_MATH_CINTERVAL_HPP_HEADER_GUARD

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"
#include "stf/math/spherical.hpp"

/**
 * @file cinterval.hpp
 * @brief A file containing a templated circular interval class along with associated functions
 */

namespace stf::math
{
/**
 * @brief An circular interval class representing a counterclockwise connected component of the circle.
 * @tparam T Number type (eg float)
 * @todo Consider renaming this to angular_interval or ainterval
 */
template <typename T>
struct cinterval final
{

    /**
     * @brief The beginning of the @ref cinterval
     */
    T a;

    /**
     * @brief The end of the @ref cinterval
     */
    T b;

    /**
     * @brief Default constructor for an cinterval: @ref a = @ref b = 0
     */
    cinterval() : a(constants<T>::zero), b(constants<T>::zero) {}

    /**
     * @brief Explicit constructor for a @ref cinterval
     * @param [in] _a
     * @param [in] _b
     */
    cinterval(T const _a, T const _b) : a(_a), b(_b) {}

    /**
     * @brief Compute whether or not the @ref cinterval is empty
     * @param [in] type Specifies whether the boundary of the @ref cinterval is open or closed
     * @return Whether or not the @ref cinterval is empty
     */
    inline bool is_empty(boundary_types type)
    {
        switch (type)
        {
        case boundary_types::closed:
            return false;
            break;
        case boundary_types::open:
            return a != b;
            break;
        default:
            return true;
        }
    }

    /**
     * @brief Compute if an @ref cinterval contains a point
     * @param [in] x Query point
     * @param [in] type Specifies whether the boundary of the @ref cinterval is open or closed
     * @return Whether or not @p this contains the value @p x
     */
    inline bool contains(T const x, boundary_types type) const
    {
        return (a <= b) ? interval<T>::contains(a, b, x, type) : !interval<T>::contains(b, a, x, complement(type));
    }

    // TODO think more about these ones
    // inline bool contains(interval const& rhs) const {  }
    // inline bool intersects(interval const& rhs) const {  }
};

} // namespace stf::math

#endif