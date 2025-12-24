#ifndef STF_ALG_STATISTICS_HPP_HEADER_GUARD
#define STF_ALG_STATISTICS_HPP_HEADER_GUARD

#include <algorithm>
#include <vector>

#include "stf/math/constants.hpp"

/**
 * @file statistics.hpp
 * @brief A file containing functions that compute statistics
 */

namespace stf::alg
{

/**
 * @brief Compute the median of a set of scalar values
 * @tparam T Number type (eg float)
 * @param values [in]
 * @return The median
 */
template <typename T>
T median(std::vector<T> const& values)
{
    std::vector<T> sorted = values;
    std::stable_sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    size_t mid = size / 2;
    if (size & static_cast<size_t>(1)) // if the size is odd, just return the middle element
    {
        return sorted[mid];
    }
    else // otherwise, average the middle two elements
    {
        T left = sorted[mid - 1];
        T right = sorted[mid];
        return math::constants<T>::half * (left + right);
    }
}

} // namespace stf::alg
#endif
