#pragma once

#include <algorithm>
#include <vector>

#include "stf/math/constants.hpp"

namespace stf::alg
{

    template<typename T>
    T median(std::vector<T> const& values)
    {
        std::vector<T> sorted = values;
        std::stable_sort(sorted.begin(), sorted.end());
        size_t size = sorted.size();
        size_t mid = size / 2;
        if (size & size_t(1))       // if the size is odd, just return the middle element
        {
            return sorted[mid];
        }
        else                        // otherwise, average the middle two elements
        {
            T left = sorted[mid - 1];
            T right = sorted[mid];
            return math::constants<T>::half * (left + right);
        }
    }

} // stf::alg