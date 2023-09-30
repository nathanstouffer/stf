#pragma once

#include <cmath>

namespace stf {
namespace math {
    
    /*
    * A base class to provide functionality common to all vectors via the CRTP
    */
    template<typename T, size_t N, typename derived_t>
    struct vec_base
    {
    private:

        inline derived_t const& crpt() const { return static_cast<derived_t const&>(*this); }
        inline derived_t& crpt() { return static_cast<derived_t&>(*this); }

    public:

        inline size_t size() const { return N; }

        inline T const& operator[](size_t i) const { return crpt().values[i]; }
        inline T& operator[](size_t i) { return crpt().values[i]; }

        inline derived_t& operator+=(derived_t const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                crpt().values[i] += rhs[i]; 
            }
            return crpt();
        }

        inline derived_t& operator-=(derived_t const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                crpt().values[i] -= rhs[i]; 
            }
            return crpt();
        }

        inline derived_t& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; ++i)
            {
                crpt().values[i] *= scalar; 
            }
            return crpt();
        }

        inline T const operator*(derived_t const& rhs) const
        {
            T dot = T(0);
            for (size_t i = 0; i < N; ++i)
            {
                dot += crpt().values[i] * rhs[i];
            }
            return dot;
        }

        inline T length() const
        {
            T dot = crpt() * crpt();
            return std::sqrt(dot);
        }

        inline derived_t& normalize()
        {
            T scalar = T(1) / length();
            crpt() *= scalar;
            return crpt();
        }

        inline derived_t normalized() const
        {
            return derived_t(crpt()).normalize();
        }

        template<typename U>
        derived_t as() const
        {
            derived_t result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = static_cast<U>(crpt().values[i]);
            }
            return result;
        }

    public:

        static inline size_t byte_size() { return sizeof(T) * N; }

    };

    /*
    * Generic vector type
    */
    template<typename T, size_t N>
    struct vec : public vec_base<T, N, vec<T, N>>
    {

        T values[N];

        constexpr vec() : vec(T(0)) {}
        explicit constexpr vec(T value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] = value;
            }
        }

    };

    /*
    * Specialization for vec2
    */
    template<typename T>
    struct vec<T, 2> : public vec_base<T, 2, vec<T, 2>>
    {

        union
        {
            T values[2];
            struct { T x, y; };
        };

        constexpr vec() : vec(T(0)) {}
        explicit constexpr vec(T value) : vec(value, value) {}
        explicit constexpr vec(T _x, T _y) : x(_x), y(_y) {}

    };

    /*
    * Specialization for vec3
    */
    template<typename T>
    struct vec<T, 3> : public vec_base<T, 3, vec<T, 3>>
    {

        union
        {
            T values[3];
            struct { T x, y, z; };
            struct { vec<T, 2> xy; };
        };

        constexpr vec() : vec(T(0)) {}
        explicit constexpr vec(T value) : vec(value, value, value) {}
        explicit constexpr vec(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        constexpr vec(vec<T, 2> const& _xy, T _z) : xy(_xy), z(_z) {}

    };

    /*
    * Specialization for vec4
    */
    template<typename T>
    struct vec<T, 4> : public vec_base<T, 4, vec<T, 4>>
    {

        union
        {
            T values[4];
            struct { T x, y, z, w; };
            struct { vec<T, 2> xy, zw; };
            struct { vec<T, 3> xyz; };
        };

        constexpr vec() : vec(T(0)) {}
        explicit constexpr vec(T value) : vec(value, value, value, value) {}
        explicit constexpr vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_z) {}
        constexpr vec(vec<T, 2> const& _xy, vec<T, 2> const& _zw) : xy(_xy), zw(_zw) {}
        constexpr vec(vec<T, 3> const& _xyz, T _w) : xyz(_xyz), w(_w) {}

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