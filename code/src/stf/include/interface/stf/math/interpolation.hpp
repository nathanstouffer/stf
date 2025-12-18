#pragma once

#include <cmath>

#include <algorithm>

#include "stf/math/vector.hpp"

/**
 * @file interpolation.hpp
 * @brief A file containing various interpolation functions
 */

namespace stf::math
{

/**
 * @brief Clamp the input time to [0, 1]
 * @tparam T Number type (eg float)
 * @param [in] t
 * @return The input clamped to [0, 1]
 */
template <typename T>
inline T clamp_time(T const t)
{
    return std::clamp(t, T(0), T(1)); // clamped
}

/**
 * @brief Smooths the input time for use in smoothstep
 *
 * This function first clamps the input to s in [0, 1] and then returns s^2 * (3 - 2 * s)
 *
 * @tparam T Number type (eg float)
 * @param [in] t
 * @return The input time smoothed close to 0 and 1
 */
template <typename T>
inline T smooth_time(T const t)
{
    T const s = clamp_time(t);        // clamped
    return s * s * (T(3) - T(2) * s); // smoothed
}

/**
 * @brief Multiply and add instruction
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] c
 * @return @p a * @p b + @p c
 */
template <typename T>
inline T mad(T const a, T const b, T const c)
{
    return a * b + c;
}

/**
 * @brief Negate the result of multiply and subtract
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] c
 * @return @p c - @p a * @p b
 */
template <typename T>
inline T nms(T const a, T const b, T const c)
{
    return c - a * b;
}

/**
 * @brief Linearly interpolate scalars
 * @note @p t is not clamped to [0, 1] (use @ref lerpstep if that is desired)
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated scalar
 */
template <typename T>
inline T lerp(T const a, T const b, T const t)
{
    return mad(t, b, nms(t, a, a));
}

/**
 * @brief Compute the inverse of @ref lerp
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] x
 * @return The inverse of @ref lerp
 */
template <typename T>
inline T lerp_inv(T const a, T const b, T const x)
{
    return (x - a) / (b - a);
}

/**
 * @brief Linearly interpolate scalars (clamped to the endpoint values)
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated scalar
 */
template <typename T>
inline T lerpstep(T const a, T const b, T const t)
{
    return lerp(a, b, clamp_time(t));
}

/**
 * @brief Interpolate smoothly between the scalar endpoints
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated scalar
 */
template <typename T>
inline T smoothstep(T const a, T const b, T const t)
{
    return lerp(a, b, smooth_time(t));
}

/**
 * @brief Interpolate between the four scalar anchors via a cubic bezier curve
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] c
 * @param [in] d
 * @param [in] t
 * @return The interpolated scalar
 */
template <typename T>
inline T cubic_bezier(T const a, T const b, T const c, T const d, T const t)
{
    // TODO simplify this implementation to just one polynomial
    // first round of lerps
    T const a1 = lerp(a, b, t);
    T const b1 = lerp(b, c, t);
    T const c1 = lerp(c, d, t);

    // second round of lerps
    T const a2 = lerp(a1, b1, t);
    T const b2 = lerp(b1, c1, t);

    // final lerp
    return lerp(a2, b2, t);
}

/**
 * @brief Interpolate between scalars using cubic hermite splines
 *
 * The spline function f(t) is defined on [0, 1] and satisfies the following constraints
 *      * f(0) = p0
 *      * f(1) = p1
 *      * f'(0) = m0
 *      * f'(1) = m1
 *
 * This can be leveraged so that consecutive splines are C^1 at the boundary of interpolation
 * intervals
 *
 * reference: https://en.wikipedia.org/wiki/Cubic_Hermite_spline
 *
 * @note Because this function assumes a domain of [0, 1], the derivatives @p m0 and @p m1 must be
 * scaled by the length of the actual interval between anchor points
 *
 * @tparam T Number type (eg float)
 * @param [in] p0 Anchor value at the beginning of the interpolation interval
 * @param [in] m0 Derivative at the beginning of the interpolation interval
 * @param [in] p1 Anchor value at the end of the interpolation interval
 * @param [in] m1 Derivative at the end of the interpolation interval
 * @param [in] t Time in [0, 1] used for interpolation
 * @return The interpolated scalar
 */
template <typename T>
inline T cubic_hermite_spline(T const p0, T const m0, T const p1, T const m1, T const t)
{
    T t_squared = t * t;
    T t_cubed = t_squared * t;

    // compute basis values
    T b0 = T(2) * t_cubed - T(3) * t_squared + T(1);
    T b1 = t_cubed - T(2) * t_squared + t;
    T b2 = T(-2) * t_cubed + T(3) * t_squared;
    T b3 = t_cubed - t_squared;

    return b0 * p0 + b1 * m0 + b2 * p1 + b3 * m1;
}

/**
 * @brief Compute the sigmoid of the input
 * @tparam T Number type (eg float)
 * @param [in] x
 * @return The output of the sigmoid function
 */
template <typename T>
inline T sigmoid(T const x)
{
    return T(1) / (T(1) + std::exp(-x));
}

/**
 * @brief Clamp a vector
 * @tparam T Number type (eg float)
 * @param [in] vec
 * @param [in] min
 * @param [in] max
 * @return The clamped vector
 */
template <class T, size_t N>
inline math::vec<T, N> clamp(math::vec<T, N> const& vec, math::vec<T, N> const& min,
                             math::vec<T, N> const& max)
{
    math::vec<T, N> result;
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = std::clamp(vec[i], min[i], max[i]);
    }
    return result;
}

/**
 * @brief Clamp a vector
 * @tparam T Number type (eg float)
 * @param [in] vec
 * @param [in] min
 * @param [in] max
 * @return The clamped vector
 */
template <class T, size_t N>
inline math::vec<T, N> clamp(math::vec<T, N> const& vec, T const min, T const max)
{
    return clamp(vec, math::vec<T, N>(min), math::vec<T, N>(max));
}

/**
 * @brief Linearly interpolate vectors
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated vector
 */
template <class T, size_t N>
inline math::vec<T, N> lerp(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
{
    math::vec<T, N> result;
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = lerp(a[i], b[i], t);
    }
    return result;
}

/**
 * @brief Linearly interpolate vectors (clamped to the endpoint values)
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated vector
 */
template <class T, size_t N>
inline math::vec<T, N> lerpstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
{
    return lerp(a, b, clamp_time(t));
}

/**
 * @brief Interpolate smoothly between the vector endpoints
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] t
 * @return The interpolated scalar
 */
template <class T, size_t N>
inline math::vec<T, N> smoothstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
{
    return lerp(a, b, smooth_time(t));
}

/**
 * @brief Interpolate between the four vector anchors via a cubic bezier curve
 * @tparam T Number type (eg float)
 * @param [in] a
 * @param [in] b
 * @param [in] c
 * @param [in] d
 * @param [in] t
 * @return The interpolated vector
 */
template <typename T, size_t N>
inline math::vec<T, N> cubic_bezier(math::vec<T, N> const a, math::vec<T, N> const b,
                                    math::vec<T, N> const c, math::vec<T, N> const d, T const t)
{
    math::vec<T, N> result;
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = cubic_bezier(a[i], b[i], c[i], d[i], t);
    }
    return result;
}

/**
 * @brief Interpolate between vectors using cubic hermite splines
 *
 * The spline function f(t) is defined on [0, 1] and satisfies the following constraints
 *      * f(0) = p0
 *      * f(1) = p1
 *      * f'(0) = m0
 *      * f'(1) = m1
 *
 * This can be leveraged so that consecutive splines are C^1 at the boundary of interpolation
 * intervals
 *
 * reference: https://en.wikipedia.org/wiki/Cubic_Hermite_spline
 *
 * @note Because this function assumes a domain of [0, 1], the derivatives @p m0 and @p m1 must be
 * scaled by the length of the actual interval between anchor points
 *
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] p0 Anchor value at the beginning of the interpolation interval
 * @param [in] m0 Derivative at the beginning of the interpolation interval
 * @param [in] p1 Anchor value at the end of the interpolation interval
 * @param [in] m1 Derivative at the end of the interpolation interval
 * @param [in] t Time in [0, 1] used for interpolation
 * @return The interpolated vector
 */
template <typename T, size_t N>
inline math::vec<T, N> cubic_hermite_spline(math::vec<T, N> const p0, math::vec<T, N> const m0,
                                            math::vec<T, N> const p1, math::vec<T, N> const m1,
                                            T const t)
{
    math::vec<T, N> result;
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = cubic_hermite_spline(p0[i], m0[i], p1[i], m1[i], t);
    }
    return result;
}

} // namespace stf::math