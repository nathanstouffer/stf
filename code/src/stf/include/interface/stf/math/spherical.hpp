#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

/**
 * @file spherical.hpp
 * @brief A file containing templated functions for spherical/circular computations
 */

namespace stf::math
{

/**
 * @brief Convert degrees to radians
 * @tparam T Number type (eg float)
 * @param [in] deg
 * @return The angle @p deg in radians
 */
template <typename T>
inline T to_radians(T const deg)
{
    return deg * math::constants<T>::deg2rad;
}

/**
 * @brief Convert radieans to degrees
 * @tparam T Number type (eg float)
 * @param [in] rad
 * @return The andle @p rad in degrees
 */
template <typename T>
inline T to_degrees(T const rad)
{
    return rad * math::constants<T>::rad2deg;
}

/**
 * @brief Compute the equivalent angle to @p theta in [0, 2pi)
 * @tparam T Number type (eg float)
 * @param [in] theta
 * @return The angle equivalent to @p theta in [0, 2pi)
 */
template <typename T>
inline T canonical_angle(T const theta)
{
    T canonical = std::fmod(theta, math::constants<T>::tau);
    if (canonical < T(0))
    {
        canonical += math::constants<T>::tau;
    }
    return canonical;
}

/**
 * @brief Of all angles that are equivalent to @p phi, compute the one closest to @p theta
 * @tparam T Number type (eg float)
 * @param [in] phi
 * @param [in] theta
 * @return The closest equivant angle of @p phi to @p theta
 */
template <typename T>
inline T closest_equiv_angle(T const phi, T const theta)
{
    T const delta = canonical_angle(phi) - canonical_angle(theta);
    return (delta <= math::constants<T>::pi) ? theta + delta : theta + delta - math::constants<T>::tau;
}

/**
 * @brief Compute the counterclockwise angle from @p u to @p v
 * @tparam T Number type (eg float)
 * @param [in] u
 * @param [in] v
 * @return The counterclockwise angle from @p u to @p v
 */
template <typename T>
inline T counterclockwise_angle(vec2<T> const& u, vec2<T> const& v)
{
    return canonical_angle(std::atan2(cross(u, v), dot(u, v)));
}

/**
 * @brief Compute unit vector in the direction of @p theta
 * @tparam T Number type (eg float)
 * @param [in] theta An angle measured counterclockwise from (1, 0)
 * @return The unit vector in the direction of @p theta
 */
template <typename T>
inline vec2<T> unit_vector(T const theta)
{
    return vec2<T>(std::cos(theta), std::sin(theta));
}

/**
 * @brief The unit vector defined by @p theta and @p phi
 * @tparam T Number type (eg float)
 * @param [in] theta An angle measured counterclockwise from (1, 0, 0)
 * @param [in] phi An angle measured from (0, 0, 1)
 * @return The unit vector defined by @p theta and @p phi
 */
template <typename T>
inline vec3<T> unit_vector(T const theta, T const phi)
{
    return vec3<T>(std::cos(theta) * std::sin(phi), std::sin(theta) * std::sin(phi), std::cos(phi));
}

/**
 * @brief Convert spherical coordinates to euclidean
 * @tparam T Number type (eg float)
 * @param [in] radius
 * @param [in] theta
 * @param [in] phi
 * @return The euclidean coordinates
 */
template <typename T>
inline math::vec3<T> to_euclidean(T const radius, T const theta, T const phi)
{
    return radius * unit_vector(theta, phi);
}

} // namespace stf::math