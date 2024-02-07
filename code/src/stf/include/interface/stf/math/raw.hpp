#pragma once

#include <cmath>

namespace stf::math::raw
{

    // TODO we might be able to implement this is as forward declared functions/classes in the vector header

    template<typename T, size_t N>
    inline void plus_equals(T lhs[N], T const rhs[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            lhs[i] += rhs[i];
        }
    }

    template<typename T, size_t N>
    inline void minus_equals(T lhs[N], T const rhs[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            lhs[i] -= rhs[i];
        }
    }

    template<typename T, size_t N>
    inline void scale(T lhs[N], T const scalar)
    {
        for (size_t i = 0; i < N; ++i)
        {
            lhs[i] *= scalar;
        }
    }

    template<typename T, size_t N>
    inline T dot(T const lhs[N], T const rhs[N])
    {
        T dot = T(0);
        for (size_t i = 0; i < N; ++i) 
        {
            dot += lhs[i] * rhs[i];
        }
        return dot;
    }

    template<typename T, typename U, size_t N>
    inline void as(T const src[N], U dst[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            dst[i] = static_cast<U>(src[i]);
        }
    }

} // stf::math::raw