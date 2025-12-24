#ifndef STF_ALG_CONTAINMENT_HPP_HEADER_GUARD
#define STF_ALG_CONTAINMENT_HPP_HEADER_GUARD

#include "stf/geom/aabb.hpp"
#include "stf/math/vector.hpp"

/**
 * @file containment.hpp
 * @brief A file containing functions that report whether or not one geometric object contains another
 */

namespace stf::alg
{

/**
 * @brief Compute whether an aabb contains a point
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] box
 * @param [in] point
 * @return Whether or not @p box contains @p point
 */
template <typename T, size_t N>
inline bool contains(geom::aabb<T, N> const& box, math::vec<T, N> const& point)
{
    return box.contains(point);
}

/**
 * @brief Compute whether an aabb contains another aabb
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] lhs
 * @param [in] rhs
 * @return Whether or not @p lhs contains @p rhs
 */
template <typename T, size_t N>
inline bool contains(geom::aabb<T, N> const& lhs, geom::aabb<T, N> const& rhs)
{
    return lhs.contains(rhs);
}

} // namespace stf::alg

#endif