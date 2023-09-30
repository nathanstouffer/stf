#pragma once

namespace stf {
namespace math {
    
    template<typename T, size_t N>
    struct vec
    {
    public:

        T values[N];

        vec() : vec(T(0)) {}
        vec(T value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] = value;
            }
        }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline size_t size() const { return N; }

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

    public:

        static inline size_t byte_size() { return sizeof(T) * N; }

    };

    template<typename T, size_t N>
    inline vec<T, N> operator+(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        return result += lhs += rhs;
    }

    template<typename T, size_t N>
    inline vec<T, N> operator-(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        return result -= lhs -= rhs;
    }

} // math
} // stf