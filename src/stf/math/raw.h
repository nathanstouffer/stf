#pragma once

namespace stf {
namespace math {
namespace raw {

    template<typename T>
    inline void plus_equals(T* lhs, T const* rhs, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            lhs[i] += rhs[i];
        }
    }

    template<typename T>
    inline void minus_equals(T* lhs, T const* rhs, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            lhs[i] -= rhs[i];
        }
    }

    template<typename T>
    inline void scale(T* lhs, T const scalar, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            lhs[i] *= scalar;
        }
    }

    template<typename T>
    inline T dot(T const* lhs, T const* rhs, size_t n)
    {
        T dot = T(0);
        for (size_t i = 0; i < n; ++i) 
        {
            dot += lhs[i] * rhs[i];
        }
        return dot;
    }

    template<typename T>
    inline T length(T const* vec, size_t n)
    {
        return std::sqrt(dot(vec, vec, n));
    }

    template<typename T>
    inline void normalize(T* vec, size_t n)
    {
        T scalar = T(1) / length(vec, n);
        for (size_t i = 0; i < n; ++i)
        {
            vec[i] *= scalar;
        }
    }

    template<typename T, typename U>
    inline void as(T const* src, U* dst, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            dst[i] = static_cast<U>(src[i]);
        }
    }

} // raw
} // math
} // stf