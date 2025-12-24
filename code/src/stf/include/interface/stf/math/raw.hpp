#ifndef STF_MATH_RAW_HPP_HEADER_GUARD
#define STF_MATH_RAW_HPP_HEADER_GUARD

#include <cmath>

/**
 * @file raw.hpp
 * @brief A file containing templated functions for working with scalars stored in raw arrays
 */

namespace stf::math::raw
{

/**
 * @brief Add to a vector (stored as an array) in place
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in,out] lhs
 * @param [in] rhs
 */
template <typename T, size_t N>
inline void plus_equals(T lhs[N], T const rhs[N])
{
    for (size_t i = 0; i < N; ++i)
    {
        lhs[i] += rhs[i];
    }
}

/**
 * @brief Subtract from a vector (stored as an array) in place
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in,out] lhs
 * @param [in] rhs
 */
template <typename T, size_t N>
inline void minus_equals(T lhs[N], T const rhs[N])
{
    for (size_t i = 0; i < N; ++i)
    {
        lhs[i] -= rhs[i];
    }
}

/**
 * @brief Scale a vector (stored as an array) in place
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in,out] lhs
 * @param [in] scalar
 */
template <typename T, size_t N>
inline void scale(T lhs[N], T const scalar)
{
    for (size_t i = 0; i < N; ++i)
    {
        lhs[i] *= scalar;
    }
}

/**
 * @brief Divide a vector (stored as an array) in place
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in,out] lhs
 * @param [in] divisor
 */
template <typename T, size_t N>
inline void divide(T lhs[N], T const divisor)
{
    for (size_t i = 0; i < N; ++i)
    {
        lhs[i] /= divisor;
    }
}

/**
 * @brief Compute the dot product of two vectors (stored as arrays)
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] lhs
 * @param [in] rhs
 * @return The dot product of @p lhs and @p rhs
 */
template <typename T, size_t N>
inline T dot(T const lhs[N], T const rhs[N])
{
    T d = T(0);
    for (size_t i = 0; i < N; ++i)
    {
        d += lhs[i] * rhs[i];
    }
    return d;
}

/**
 * @brief Compute the hadamard product of two vectors (stored as arrays) in place
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in,out] lhs
 * @param [in] rhs
 */
template <typename T, size_t N>
inline void hadamard_equals(T lhs[N], T const rhs[N])
{
    for (size_t i = 0; i < N; ++i)
    {
        lhs[i] *= rhs[i];
    }
}

/**
 * @brief Write the prefix of one array into another
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [out] lhs
 * @param [in] rhs
 */
template <typename T, size_t N>
inline void prefix(T lhs[N - 1], T const rhs[N])
{
    for (size_t i = 0; i < N - 1; ++i)
    {
        lhs[i] = rhs[i];
    }
}

/**
 * @brief Cast a vector (stored as an array) to a different precision
 * @tparam T Source number type (eg float)
 * @tparam U Destination number type (eg double)
 * @tparam N Dimension
 * @param [in] src
 * @param [in,out] dst
 */
template <typename T, typename U, size_t N>
inline void as(T const src[N], U dst[N])
{
    for (size_t i = 0; i < N; ++i)
    {
        dst[i] = static_cast<U>(src[i]);
    }
}

} // namespace stf::math::raw
#endif
