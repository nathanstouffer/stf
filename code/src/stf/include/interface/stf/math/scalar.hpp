#pragma once

#include <cmath>

namespace stf {
namespace math {

    template<typename T>
    inline bool const equ(T const lhs, T const rhs, T const eps)
    {
        return (std::abs(lhs - rhs) <= eps) ? true : false;
    }

    template<typename T>
    inline bool const neq(T const lhs, T const rhs, T const eps)
    {
        return !equ(lhs, rhs, eps);
    }

} // math
} // stf