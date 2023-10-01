#pragma once

#include <cmath>

#include "raw.h"

namespace stf {
namespace math {
    
    /*
    * NOTE: Unfortunately there is a lot of duplication between among the generic vector class and the specializations when
    * the dimension is specialized for N = 2, 3, 4. This could be avoided by paring Curiously Recurring Template Pattern
    * with some casting to the derived class type. But I opted for simplicity even though it involves more duplication. To
    * reduce some of the unwanted duplication, many of the member functions call through to templated functions that operate
    * directly on the underlying raw pointers
    */

    // Generic vector type
    template<typename T, size_t N>
    struct vec
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

        inline size_t size() const { return N; }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, N>(values, rhs.values); return *this; }
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, N>(values, rhs.values); return *this; }

        inline vec& operator*=(T scalar) { raw::scale<T, N>(values, scalar); return *this; }

        inline T const operator*(vec const& rhs) const { return raw::dot<T, N>(values, rhs.values); }
        inline T length() const { return raw::length<T, N>(values); }

        inline vec& normalize() { raw::normalize<T, N>(values); return *this; }
        inline vec normalized() const { return vec(*this).normalize(); }

        template<typename U>
        vec<U, N> as() const
        {
            vec<U, N> result;
            raw::as<T, U, N>(values, result.values, N);
            return result;
        }

    public:

        static inline size_t byte_count() { return sizeof(T) * N; }

    };

    // Specialization for vec2
    template<typename T>
    struct vec<T, 2>
    {

        union
        {
            T values[2];
            struct { T x, y; };
        };

        constexpr vec() : vec(T(0)) {}
        explicit constexpr vec(T value) : vec(value, value) {}
        explicit constexpr vec(T _x, T _y) : x(_x), y(_y) {}

        inline size_t size() const { return 2; }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 2>(values, rhs.values); return *this; }
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 2>(values, rhs.values); return *this; }

        inline vec& operator*=(T scalar) { raw::scale<T, 2>(values, scalar); return *this; }

        inline T const operator*(vec const& rhs) const { return raw::dot<T, 2>(values, rhs.values); }
        inline T length() const { return raw::length<T, 2>(values); }

        inline vec& normalize() { raw::normalize<T, 2>(values); return *this; }
        inline vec normalized() const { return vec(*this).normalize(); }

        template<typename U>
        vec<U, 2> as() const
        {
            vec<U, 2> result;
            raw::as<T, U, 2>(values, result.values);
            return result;
        }

    public:

        static inline size_t byte_count() { return sizeof(T) * 2; }

    };

    /*
    * Specialization for vec3
    */
    template<typename T>
    struct vec<T, 3>
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

        inline size_t size() const { return 3; }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 3>(values, rhs.values); return *this; }
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 3>(values, rhs.values); return *this; }

        inline vec& operator*=(T scalar) { raw::scale<T, 3>(values, scalar); return *this; }

        inline T const operator*(vec const& rhs) const { return raw::dot<T, 3>(values, rhs.values); }
        inline T length() const { return raw::length<T, 3>(values); }

        inline vec& normalize() { raw::normalize<T, 3>(values); return *this; }
        inline vec normalized() const { return vec(*this).normalize(); }

        template<typename U>
        vec<U, 3> as() const
        {
            vec<U, 3> result;
            raw::as<T, U, 3>(values, result.values);
            return result;
        }

    public:

        static inline size_t byte_count() { return sizeof(T) * 3; }

    };

    /*
    * Specialization for vec4
    */
    template<typename T>
    struct vec<T, 4>
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

        inline size_t size() const { return 4; }

        inline T const& operator[](size_t i) const { return values[i]; }
        inline T& operator[](size_t i) { return values[i]; }

        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 4>(values, rhs.values); return *this; }
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 4>(values, rhs.values); return *this; }

        inline vec& operator*=(T scalar) { raw::scale<T, 4>(values, scalar); return *this; }

        inline T const operator*(vec const& rhs) const { return raw::dot<T, 4>(values, rhs.values); }
        inline T length() const { return raw::length<T, 4>(values); }

        inline vec& normalize() { raw::normalize<T, 4>(values); return *this; }
        inline vec normalized() const { return vec(*this).normalize(); }

        template<typename U>
        vec<U, 4> as() const
        {
            vec<U, 4> result;
            raw::as<T, U, 4>(values, result.values);
            return result;
        }

    public:

        static inline size_t byte_count() { return sizeof(T) * 4; }

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
    inline vec<T, N> const operator-(vec<T, N> const& lhs)
    {
        vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = -lhs[i];
        }
        return result;
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
    inline vec<T, N> const operator*(vec<T, N> const& lhs, T const scalar)
    {
        return vec<T, N>(lhs) *= scalar;
    }

    template<typename T, size_t N>
    inline vec<T, N> const operator*(T const scalar, vec<T, N> const& rhs)
    {
        return rhs * scalar;
    }

    template<typename T, size_t N>
    inline T const dot(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return lhs * rhs;
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