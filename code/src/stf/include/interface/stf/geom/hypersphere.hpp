#pragma once

#include "stf/math/vector.hpp"

/**
 * @file hypersphere.hpp
 * @brief A file containing a templated hypersphere class along with associated functions
 */

namespace stf::geom
{

/**
 * @brief A class representing a hypersphere in R^n
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 */
template <typename T, size_t N>
struct hypersphere final
{

    /**
     * @brief Type alias for vector type
     */
    using vec_t = math::vec<T, N>;

public:
    /**
     * @brief The center of the hypersphere
     */
    vec_t center;

    /**
     * @brief The radius of the hypersphere
     */
    T radius;

    /**
     * @brief Construct from a center point and radius
     * @param [in] _center
     * @param [in] _radius
     */
    hypersphere(vec_t const& _center, T const _radius) : center(_center), radius(_radius) {}

    /**
     * @brief Compute whether or not the hypersphere encloses a point
     * @param [in] query
     * @return Whether or not @p this encloses @p query
     */
    bool encloses(vec_t const& query) const
    {
        vec_t delta = query - center;
        return delta.length_squared() <= radius * radius;
    }
};

/// @cond DELETED
/**
 * @brief Delete invalid sphere specialization
 */
template <typename T>
struct hypersphere<T, 0>
{
    hypersphere() = delete;
};
/// @endcond

/**
 * @brief Type alias for a @ref hypersphere in 2 dimensions -- a circle
 * @tparam T Number type (eg float)
 */
template <typename T>
using circle = hypersphere<T, 2>;

/**
 * @brief Type alias for a @ref hypersphere in 3 dimensions -- a sphere
 * @tparam T Number type (eg float)
 */
template <typename T>
using sphere = hypersphere<T, 3>;

} // namespace stf::geom