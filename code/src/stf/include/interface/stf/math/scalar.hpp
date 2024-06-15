#pragma once

#include <cmath>

/**
 * @file scalar.hpp
 * @brief A file containing a templated functions dealing with scalar values
 */

namespace stf::math
{

    /**
     * @brief Compute whether two scalars are less than or equal to @p eps apart
     * @tparam T Number type (eg float)
     * @param [in] lhs 
     * @param [in] rhs 
     * @param [in] eps 
     * @return Whether or not @p lhs and @p rhs are less than or equal to @p eps apart
     */
    template<typename T>
    inline bool const equ(T const lhs, T const rhs, T const eps)
    {
        return (std::abs(lhs - rhs) <= eps) ? true : false;
    }

    /**
     * @brief Compute whether two scalars are greater than @p eps apart
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] eps
     * @return Whether or not @p lhs and @p rhs are greater than @p eps apart
     */
    template<typename T>
    inline bool const neq(T const lhs, T const rhs, T const eps)
    {
        return !equ(lhs, rhs, eps);
    }

} // stf::math