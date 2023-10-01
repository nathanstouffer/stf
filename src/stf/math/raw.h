#pragma once

namespace stf {
namespace math {
namespace raw {

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

    template<typename T, size_t N>
    inline T length(T const vec[N])
    {
        return std::sqrt(dot<T, N>(vec, vec));
    }

    template<typename T, size_t N>
    inline void normalize(T vec[N])
    {
        T scalar = T(1) / length<T, N>(vec);
        for (size_t i = 0; i < N; ++i)
        {
            vec[i] *= scalar;
        }
    }

    template<typename T, typename U, size_t N>
    inline void as(T const src[N], U dst[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            dst[i] = static_cast<U>(src[i]);
        }
    }

} // raw
} // math
} // stf