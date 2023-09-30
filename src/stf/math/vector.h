#pragma once

#include <cmath>

namespace stf {
namespace math {
    
    template<typename T, size_t N>
    struct vec
    {
    public:

        T values[N];

        vec() : vec(T(0)) {}
        explicit vec(T value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] = value;
            }
        }

        inline size_t size() const { return N; }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline vec<T, N>& operator+=(vec<T, N> const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] += rhs[i]; 
            }
            return *this;
        }

        inline vec<T, N>& operator-=(vec<T, N> const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] -= rhs[i]; 
            }
            return *this;
        }

        inline vec<T, N>& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] *= scalar; 
            }
            return *this;
        }

        inline T length() const
        {
            T dot = T(0);
            for (size_t i = 0; i < N; ++i)
            {
                dot += values[i] * values[i];
            }
            return std::sqrt(dot);
        }

        inline vec<T, N>& normalize()
        {
            T scalar = T(1) / length();
            *this *= scalar;
            return *this;
        }

        inline vec<T, N> normalized() const
        {
            vec<T, N> result = *this;
            return result.normalize();
        }

        template<typename U>
        vec<U, N> as() const
        {
            vec<U, N> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = static_cast<U>(values[i]);
            }
            return result;
        }

    public:

        static inline size_t byte_size() { return sizeof(T) * N; }

    };

    template<typename T, size_t N>
    inline bool const equ(vec<T, N> const& lhs, vec<T, N> const& rhs, T tol)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (std::abs(lhs[i] - rhs[i]) > tol)
            {
                return false;
            }
        }
        return true;
    }

    template<typename T, size_t N>
    inline bool const neq(vec<T, N> const& lhs, vec<T, N> const& rhs, T tol)
    {
        return !equ(lhs, rhs, tol);
    }

    template<typename T, size_t N>
    inline bool const operator==(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    template<typename T, size_t N>
    inline bool const operator!=(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return !(lhs == rhs);
    }

    template<typename T, size_t N>
    inline vec<T, N> const operator+(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return vec<T, N>(lhs) += rhs;
    }

    template<typename T, size_t N>
    inline vec<T, N> const operator-(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return vec<T, N>(lhs) -= rhs;
    }

    template<typename T, size_t N>
    inline T const operator*(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        T result = T(0);
        for (size_t i = 0; i < N; ++i)
        {
            result += lhs[i] * rhs[i];
        }
        return result;
    }

    template<typename T, size_t N>
    inline vec<T, N> const hadamard(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = lhs[i] * rhs[i];
        }
        return result;
    }

} // math
} // stf

namespace std {

    template<typename T, size_t N>
    struct hash<stf::math::vec<T, N>>
    {
        size_t operator()(stf::math::vec<T, N> const& rhs) const
        {
            std::hash<T> hasher;
            size_t result = 17;
            for (size_t i = 0; i < N; ++i)
            {
                result = result * 23 + hasher(rhs[i]);
            }
            return result;
        }
    };

} // std