#pragma once

#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

/**
 * @file transform.hpp
 * @brief A file containing a templated functionality dealing with named transformations of mathematical objects
 */

namespace stf::math
{

/**
 * @brief Rotate a @p point counterclockwise around the origin by @p theta radians
 * @tparam T Number type (eg float)
 * @param [in] point
 * @param [in] theta
 * @return The rotated point
 */
template <typename T>
inline math::vec2<T> rotate(math::vec2<T> const& point, T const theta)
{
    return math::rotate<T>(theta) * point;
}

/**
 * @brief Orbit @p point counterclockwise around @p focus by @p theta radians
 * @tparam T Number type (eg float)
 * @param [in] point
 * @param [in] focus
 * @param [in] theta
 * @return The orbited point
 */
template <typename T>
inline math::vec2<T> orbit(math::vec2<T> const& point, math::vec2<T> const& focus, T const theta)
{
    return rotate(point - focus, theta) + focus;
}

/**
 * @brief Rotate @p point about @p axis by @p theta radians
 * @tparam T
 * @param [in] point
 * @param [in] axis
 * @param [in] theta
 * @note @p axis must be a unit vector
 * @note Rotates in the direction of the right-hand rule
 * @return The rotated point
 */
template <typename T>
inline math::vec3<T> rotate(math::vec3<T> const& point, math::vec3<T> const& axis, T const theta)
{
    math::vec3<T> const c = dot(axis, point) * axis;         // the center of our circle about the rotation axis
    math::vec3<T> const x = cross(cross(axis, point), axis); // the x direction of the circle
    math::vec3<T> const y = cross(axis, point);              // the y direction of the circle
    return c + x * std::cos(theta) + y * std::sin(theta);
}

/**
 * @brief Orbits @p point around @p focus by @p delta_phi and @p delta_theta
 * @tparam T Number type (eg float)
 * @param [in] point
 * @param [in] focus Center point of the orbit
 * @param [in] right Direction defining what direction is to the right
 * @param [in] delta_phi
 * @param [in] delta_theta
 * @note Angles @p delta_phi and @p delta_theta are spherical coordinates measured with @p focus as the origin
 * @note @p right must be a unit vector
 * @return The orbited point
 */
template <typename T>
inline math::vec3<T> orbit(math::vec3<T> const& point, math::vec3<T> const& focus, math::vec3<T> const& right,
                           T const delta_phi, T const delta_theta)
{
    math::vec3<T> relative = point - focus;
    relative = rotate(relative, right, delta_phi);
    relative = rotate(relative, math::vec3<T>(0, 0, 1), delta_theta);
    return relative + focus;
}

} // namespace stf::math