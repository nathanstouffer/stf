#pragma once

#include <algorithm>
#include <vector>

#include "stf/math/constants.h"

namespace stf::alg
{

    template<typename T>
    T median(std::vector<T> const& values)
    {
        std::vector<T> sorted = values;
        std::stable_sort(sorted.begin(), sorted.end());
        size_t size = sorted.size();
        if (size % 2 == 0)
        {
            T left = sorted[(size / 2) - 1];
            T right = sorted[size / 2];
            return math::constants<T>::half * (left + right);
        }
        else
        {
            return sorted[size / 2]
        }
    }

} // stf::alg