#ifndef STF_MATH_BASIS_HPP_HEADER_GUARD
#define STF_MATH_BASIS_HPP_HEADER_GUARD

#include <array>

#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

/**
 * @file basis.hpp
 * @brief A file containing items related to a basis for R^n
 */

namespace stf::math
{
/**
 * @brief Type alias for the basis of the box
 * @note The basis is assumed to be orthonormal
 */

/**
 * @brief Type alias for a basis of R^n
 * @note No verification is performed
 */
template <typename T, size_t N>
using basis = std::array<vec<T, N>, N>;

/**
 * @brief Compute the canonical basis for the dimension of the
 * @return The canonical basis of R^n
 */
template <typename T, size_t N>
basis<T, N> canonical_basis()
{
    basis<T, N> ret;
    for (size_t d = 0; d < N; ++d)
    {
        vec<T, N> dir = vec<T, N>(math::constants<T>::zero);
        dir[d] = math::constants<T>::one;
        ret[d] = dir;
    }
    return ret;
}

/**
 * @brief Convert a rotation matrix to a basis
 * @param [in] rotation
 * @return The basis corresponding to @p rotation
 * @note @p rotation is assumed to be orthonormal
 */
template <typename T, size_t N>
basis<T, N> to_basis(mtx<T, N> const& rotation)
{
    basis<T, N> ret;
    for (size_t d = 0; d < N; ++d)
    {
        ret[d] = rotation.col(d);
    }
    return ret;
}

} // namespace stf::math
#endif
