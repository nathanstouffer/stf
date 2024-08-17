#pragma once

#include <cmath>

#include <iostream>

#include "stf/math/constants.hpp"
#include "stf/math/raw.hpp"

/**
 * @file vector.hpp
 * @brief A file containing a templated vector class along with associated functions
 */

namespace stf::math
{
    
    /**
     * @brief A class representing elements of R^n
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * 
     * @todo Possibly use the CRTP to reduce verbosity -- just make sure to test performance/memory layout implications.
     * Unfortunately there is a lot of duplication between the generic vector class and the specializations when
     * the dimension is specialized for N = 2, 3, 4. This could be avoided by pairing Curiously Recurring Template Pattern
     * with some casting to the derived class type. But I opted for simplicity even though it involves more duplication. To
     * reduce some of the unwanted duplication, many of the member functions call through to templated functions that operate
     * directly on the underlying raw pointers
     */
    template<typename T, size_t N>
    struct vec final
    {

        /**
         * @brief A raw array to store the values making up the vector
         */
        T values[N];

        /**
         * @brief Default constructor -- intializes all dimensions to 0
         */
        constexpr vec() : vec(T(0)) {}

        /**
         * @brief Construct from a single scalar -- initializes all dimensions to @p value
         * @param [in] value 
         */
        explicit constexpr vec(T const value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                values[i] = value;
            }
        }

        /**
         * @brief Construct from a N - 1 dimensional vector and a scalar
         * 
         * @p prefix is used to fill the first N - 1 dimensions and @p scalar is used as the value for the N dimension
         * 
         * @param [in] prefix 
         * @param [in] suffix 
         */
        constexpr vec(vec<T, N - 1> const& prefix, T const suffix)
        {
            for (size_t i = 0; i < N - 1; ++i) { values[i] = prefix[i]; }
            values[N - 1] = suffix;
        }

        /**
         * @brief Construct from a raw array of scalars
         * @param [in] elements 
         */
        constexpr vec(T const elements[N])
        {
            for (size_t i = 0; i < N; ++i) { values[i] = elements[i]; }
        }

        /**
         * @brief Return the dimension of the vector
         * @return The dimension of the vector 
         */
        inline size_t size() const { return N; }
        
        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A const reference to the scalar at dimension @p i
         */
        inline T const& operator[](size_t i) const { return values[i]; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A reference to the scalar at dimension @p i
         */
        inline T& operator[](size_t i) { return values[i]; }

        /**
         * @brief Add to a vector in place
         * @param [in] rhs 
         * @return A reference to @p this
         */
        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, N>(values, rhs.values); return *this; }

        /**
         * @brief Subtract from a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, N>(values, rhs.values); return *this; }

        /**
         * @brief Scale a vector in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        inline vec& operator*=(T const scalar) { raw::scale<T, N>(values, scalar); return *this; }

        /**
         * @brief Compute a dot product
         * @param [in] rhs 
         * @return The dot product of @p this with @p rhs
         */
        inline T const operator*(vec const& rhs) const { return raw::dot<T, N>(values, rhs.values); }

        /**
         * @brief Compute the square of the length of a vector
         * @return The length squared of @p this
         */
        inline T length_squared() const { return *this * *this;  }

        /**
         * @brief Compute the length of a vector
         * @return The length of @p this
         */
        inline T length() const { return std::sqrt(length_squared()); }

        /**
         * @brief Normalize a vector in place
         * @return A reference to @p this
         */
        inline vec& normalize() { return *this *= (T(1.0) / length()); }

        /**
         * @brief Compute a normalized vector
         * @return A normal vector in the direction of @p this
         */
        inline vec normalized() const { return vec(*this).normalize(); }

        /**
         * @brief Compute the component of a vector in the direction of another vector
         * @param [in] rhs The direction of the projection
         * @return The component of @p this in the direction of @p rhs
         */
        inline vec projected_on(vec const& rhs) const { T scalar = (*this * rhs) / (rhs * rhs); return scalar * rhs; }

        /**
         * @brief Compute the component of a vector orthogonal to another vector
         * @param [in] rhs The direction orthogonal to the projection
         * @return The component of @p this orthogonal to @p rhs
         */
        inline vec orthogonal_to(vec const& rhs) const { return vec(*this) -= projected_on(rhs); }

        /**
         * @brief Cast a vector to a different precision
         * @tparam U Destination number type (eg float)
         * @return @p this casted to the precision of @p U
         */
        template<typename U>
        vec<U, N> as() const
        {
            vec<U, N> result;
            raw::as<T, U, N>(values, result.values, N);
            return result;
        }

    public:

        /**
         * @brief Compute the number of bytes allocated by vector
         * @return The byte count
         */
        static inline size_t byte_count() { return sizeof(T) * N; }

    };

    /**
     * @brief Specialization of @ref vec for N=2
     * @tparam T Number type (eg float)
     */
    template<typename T>
    struct vec<T, 2> final
    {

        /**
         * @brief A union of a raw scalar array of size 2 and a struct containing scalar members x/y
         * 
         * This enables access to the x/y components directly
         */
        union
        {
            /// @cond DELETED
            T values[2];
            struct { T x, y; };
            /// @endcond
        };

        /**
         * @brief Default constructor -- intiliazes all dimensions to 0
         */
        constexpr vec() : vec(T(0)) {}

        /**
         * @brief Construct from a single scalar -- initializes all dimensions to @p value
         * @param [in] value
         */
        explicit constexpr vec(T const value) : vec(value, value) {}

        /**
         * @brief Construct from two scalars
         * @param [in] _x 
         * @param [in] _y 
         */
        explicit constexpr vec(T const _x, T const _y) : x(_x), y(_y) {}

        /**
         * @brief Return the dimension of the vector
         * @return The dimension of the vector
         */
        inline size_t size() const { return 2; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A const reference to the scalar at dimension @p i
         */
        inline T const& operator[](size_t i) const { return values[i]; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A reference to the scalar at dimension @p i
         */
        inline T& operator[](size_t i) { return values[i]; }

        /**
         * @brief Add to a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 2>(values, rhs.values); return *this; }

        /**
         * @brief Subtract from a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 2>(values, rhs.values); return *this; }

        /**
         * @brief Scale a vector in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        inline vec& operator*=(T const scalar) { raw::scale<T, 2>(values, scalar); return *this; }

        /**
         * @brief Compute a dot product
         * @param [in] rhs
         * @return The dot product of @p this with @p rhs
         */
        inline T const operator*(vec const& rhs) const { return raw::dot<T, 2>(values, rhs.values); }

        /**
         * @brief Compute the square of the length of a vector
         * @return The length squared of @p this
         */
        inline T length_squared() const { return *this * *this; }

        /**
         * @brief Compute the length of a vector
         * @return The length of @p this
         */
        inline T length() const { return std::sqrt(length_squared()); }

        /**
         * @brief Normalize a vector in place
         * @return A reference to @p this
         */
        inline vec& normalize() { return *this *= (T(1.0) / length()); }

        /**
         * @brief Compute a normalized vector
         * @return A normal vector in the direction of @p this
         */
        inline vec normalized() const { return vec(*this).normalize(); }

        /**
         * @brief Compute the component of a vector in the direction of another vector
         * @param [in] rhs The direction of the projection
         * @return The component of @p this in the direction of @p rhs
         */
        inline vec projected_on(vec const& rhs) const { T scalar = (*this * rhs) / (rhs * rhs); return scalar * rhs; }

        /**
         * @brief Compute the component of a vector orthogonal to another vector
         * @param [in] rhs The direction orthogonal to the projection
         * @return The component of @p this orthogonal to @p rhs
         */
        inline vec orthogonal_to(vec const& rhs) const { return vec(*this) -= projected_on(rhs); }

        /**
         * @brief Cast a vector to a different precision
         * @tparam U Destination number type (eg float)
         * @return @p this casted to the precision of @p U
         */
        template<typename U>
        vec<U, 2> as() const
        {
            vec<U, 2> result;
            raw::as<T, U, 2>(values, result.values);
            return result;
        }

    public:

        /**
         * @brief Compute the number of bytes allocated by vector
         * @return The byte count
         */
        static inline size_t byte_count() { return sizeof(T) * 2; }

    };

    /**
     * @brief Specialization of @ref vec for N=3
     * @tparam T Number type (eg float)
     */
    template<typename T>
    struct vec<T, 3> final
    {

        /**
         * @brief A union of a raw scalar array of size 3 and various structs allowing granular member access
         */
        union
        {
            /// @cond DELETED
            T values[3];
            struct { T x, y, z; };
            struct { vec<T, 2> xy; };
            /// @endcond
        };

        /**
         * @brief Default constructor -- intiliazes all dimensions to 0
         */
        constexpr vec() : vec(T(0)) {}

        /**
         * @brief Construct from a single scalar -- initializes all dimensions to @p value
         * @param [in] value
         */
        explicit constexpr vec(T const value) : vec(value, value, value) {}
        
        /**
         * @brief Construct from three scalars
         * @param [in] _x 
         * @param [in] _y 
         * @param [in] _z 
         */
        explicit constexpr vec(T const _x, T const _y, T const _z) : x(_x), y(_y), z(_z) {}
        
        /**
         * @brief Construct from a vec2 and a scalar
         * @param [in] _xy 
         * @param [in] _z 
         */
        constexpr vec(vec<T, 2> const& _xy, T const _z) : vec(_xy.x, _xy.y, _z) {}

        /**
         * @brief Return the dimension of the vector
         * @return The dimension of the vector
         */
        inline size_t size() const { return 3; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A const reference to the scalar at dimension @p i
         */
        inline T const& operator[](size_t i) const { return values[i]; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A reference to the scalar at dimension @p i
         */
        inline T& operator[](size_t i) { return values[i]; }

        /**
         * @brief Add to a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 3>(values, rhs.values); return *this; }

        /**
         * @brief Subtract from a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 3>(values, rhs.values); return *this; }

        /**
         * @brief Scale a vector in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        inline vec& operator*=(T const scalar) { raw::scale<T, 3>(values, scalar); return *this; }

        /**
         * @brief Compute a dot product
         * @param [in] rhs
         * @return The dot product of @p this with @p rhs
         */
        inline T const operator*(vec const& rhs) const { return raw::dot<T, 3>(values, rhs.values); }

        /**
         * @brief Compute the square of the length of a vector
         * @return The length squared of @p this
         */
        inline T length_squared() const { return *this * *this; }

        /**
         * @brief Compute the length of a vector
         * @return The length of @p this
         */
        inline T length() const { return std::sqrt(length_squared()); }

        /**
         * @brief Normalize a vector in place
         * @return A reference to @p this
         */
        inline vec& normalize() { return *this *= (T(1.0) / length()); }

        /**
         * @brief Compute a normalized vector
         * @return A normal vector in the direction of @p this
         */
        inline vec normalized() const { return vec(*this).normalize(); }

        /**
         * @brief Compute the component of a vector in the direction of another vector
         * @param [in] rhs The direction of the projection
         * @return The component of @p this in the direction of @p rhs
         */
        inline vec projected_on(vec const& rhs) const { T scalar = (*this * rhs) / (rhs * rhs); return scalar * rhs; }
        
        /**
         * @brief Compute the component of a vector orthogonal to another vector
         * @param [in] rhs The direction orthogonal to the projection
         * @return The component of @p this orthogonal to @p rhs
         */
        inline vec orthogonal_to(vec const& rhs) const { return vec(*this) -= projected_on(rhs); }

        /**
         * @brief Cast a vector to a different precision
         * @tparam U Destination number type (eg float)
         * @return @p this casted to the precision of @p U
         */
        template<typename U>
        vec<U, 3> as() const
        {
            vec<U, 3> result;
            raw::as<T, U, 3>(values, result.values);
            return result;
        }

    public:

        /**
         * @brief Compute the number of bytes allocated by vector
         * @return The byte count
         */
        static inline size_t byte_count() { return sizeof(T) * 3; }

    };

    /**
     * @brief Specialization of @ref vec for N=4
     * @tparam T Number type (eg float)
     */
    template<typename T>
    struct vec<T, 4> final
    {

        /**
         * @brief A union of a raw scalar array of size 4 and various structs allowing granular member access
         */
        union
        {
            /// @cond DELETED
            T values[4];
            struct { T x, y, z, w; };
            struct { vec<T, 2> xy, zw; };
            struct { vec<T, 3> xyz; };
            /// @endcond
        };

        /**
         * @brief Default constructor -- intiliazes all dimensions to 0
         */
        constexpr vec() : vec(T(0)) {}

        /**
         * @brief Construct from a single scalar -- initializes all dimensions to @p value
         * @param [in] value
         */
        explicit constexpr vec(T value) : vec(value, value, value, value) {}

        /**
         * @brief Construct from 4 scalars
         * @param [in] _x 
         * @param [in] _y 
         * @param [in] _z 
         * @param [in] _w 
         */
        explicit constexpr vec(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

        /**
         * @brief Construct from two vec2s
         * @param [in] _xy 
         * @param [in] _zw 
         */
        constexpr vec(vec<T, 2> const& _xy, vec<T, 2> const& _zw) : vec(_xy.x, _xy.y, _zw.x, _zw.y) {}

        /**
         * @brief Construct from a vec3 and a scalar
         * @param [in] _xyz 
         * @param [in] _w 
         */
        constexpr vec(vec<T, 3> const& _xyz, T _w) : vec(_xyz.x, _xyz.y, _xyz.z, _w) {}

        /**
         * @brief Return the dimension of the vector
         * @return The dimension of the vector
         */
        inline size_t size() const { return 4; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A const reference to the scalar at dimension @p i
         */
        inline T const& operator[](size_t i) const { return values[i]; }

        /**
         * @brief Return a scalar from the vector
         * @param [in] i The dimension of the vector to read
         * @return A reference to the scalar at dimension @p i
         */
        inline T& operator[](size_t i) { return values[i]; }

        /**
         * @brief Add to a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator+=(vec const& rhs) { raw::plus_equals<T, 4>(values, rhs.values); return *this; }

        /**
         * @brief Subtract from a vector in place
         * @param [in] rhs
         * @return A reference to @p this
         */
        inline vec& operator-=(vec const& rhs) { raw::minus_equals<T, 4>(values, rhs.values); return *this; }

        /**
         * @brief Scale a vector in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        inline vec& operator*=(T const scalar) { raw::scale<T, 4>(values, scalar); return *this; }

        /**
         * @brief Compute a dot product
         * @param [in] rhs
         * @return The dot product of @p this with @p rhs
         */
        inline T const operator*(vec const& rhs) const { return raw::dot<T, 4>(values, rhs.values); }

        /**
         * @brief Compute the square of the length of a vector
         * @return The length squared of @p this
         */
        inline T length_squared() const { return *this * *this; }

        /**
         * @brief Compute the length of a vector
         * @return The length of @p this
         */
        inline T length() const { return std::sqrt(length_squared()); }

        /**
         * @brief Normalize a vector in place
         * @return A reference to @p this
         */
        inline vec& normalize() { return *this *= (T(1.0) / length()); }

        /**
         * @brief Compute a normalized vector
         * @return A normal vector in the direction of @p this
         */
        inline vec normalized() const { return vec(*this).normalize(); }

        /**
         * @brief Compute the component of a vector in the direction of another vector
         * @param [in] rhs The direction of the projection
         * @return The component of @p this in the direction of @p rhs
         */
        inline vec projected_on(vec const& rhs) const { T scalar = (*this * rhs) / (rhs * rhs); return scalar * rhs; }

        /**
         * @brief Compute the component of a vector orthogonal to another vector
         * @param [in] rhs The direction orthogonal to the projection
         * @return The component of @p this orthogonal to @p rhs
         */
        inline vec orthogonal_to(vec const& rhs) const { return vec(*this) -= projected_on(rhs); }

        /**
         * @brief Cast a vector to a different precision
         * @tparam U Destination number type (eg float)
         * @return @p this casted to the precision of @p U
         */
        template<typename U>
        vec<U, 4> as() const
        {
            vec<U, 4> result;
            raw::as<T, U, 4>(values, result.values);
            return result;
        }

    public:

        /**
         * @brief Compute the number of bytes allocated by vector
         * @return The byte count
         */
        static inline size_t byte_count() { return sizeof(T) * 4; }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid vector specialization
     */
    template<typename T> struct vec<T, 0> { vec() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2D @ref vec
     * @tparam T Number type (eg float)
     */
    template<typename T> using vec2 = vec<T, 2>;

    /**
     * @brief Type alias for a 3D @ref vec
     * @tparam T Number type (eg float)
     */
    template<typename T> using vec3 = vec<T, 3>;

    /**
     * @brief Type alias for a 4D @ref vec
     * @tparam T Number type (eg float)
     */
    template<typename T> using vec4 = vec<T, 4>;

    /**
     * @brief Compute the squareof the distance between @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The square of the distance between @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline T const dist_squared(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return (lhs - rhs).length_squared();
    }

    /** 
     * @brief Compute the distance between @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The distance between @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline T const dist(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return (lhs - rhs).length();
    }

    /** 
     * @brief Compute whether the distance between @p lhs and @p rhs is less than or equal to @p eps
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] eps The epsilon distance to use when computating approximate equality
     * @return Whether or not @p lhs and @p rhs are closer than @p eps
     */
    template<typename T, size_t N>
    inline bool const equ(vec<T, N> const& lhs, vec<T, N> const& rhs, T const eps)
    {
        return (dist(lhs, rhs) <= eps) ? true : false;
    }

    /**
     * @brief Compute whether the distance between @p lhs and @p rhs is strictly greater than eps
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] eps The epsilon distance to use when computating approximate equality
     * @return Whether or not @p lhs and @p rhs are further apart than @p eps
     */
    template<typename T, size_t N>
    inline bool const neq(vec<T, N> const& lhs, vec<T, N> const& rhs, T eps)
    {
        return !equ(lhs, rhs, eps);
    }

    /** 
     * @brief Compute whether @p lhs is approximately equal to @p rhs (uses constants<T>::tol as epsilon)
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs and @p rhs are approximately equal
     */
    template<typename T, size_t N>
    inline bool const operator==(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return equ(lhs, rhs, constants<T>::tol);
    }

    /**
     * @brief Compute whether @p lhs is approximately not equal to @p rhs (uses constants<T>::tol as epsilon)
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs and @p rhs are approximately not equal
     */
    template<typename T, size_t N>
    inline bool const operator!=(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Compute the negative of @p lhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @return The negative of @p lhs
     */
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

    /**
     * @brief Compute the sum of @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The sum of @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator+(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return vec<T, N>(lhs) += rhs;
    }

    /**
     * @brief Compute the difference of @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The difference of @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator-(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return vec<T, N>(lhs) -= rhs;
    }

    /**
     * @brief Scale @p lhs by @p scalar
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] scalar
     * @return @p lhs scaled by @p scalar
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator*(vec<T, N> const& lhs, T const scalar)
    {
        return vec<T, N>(lhs) *= scalar;
    }

    /**
     * @brief Scale @p rhs by by @p scalar
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] scalar
     * @param [in] rhs
     * @return @p rhs scaled by @p scalar
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator*(T const scalar, vec<T, N> const& rhs)
    {
        return rhs * scalar;
    }

    /**
     * @brief Compute the dot product of @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The dot product of @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline T const dot(vec<T, N> const& lhs, vec<T, N> const& rhs)
    {
        return lhs * rhs;
    }

    /** 
     * @brief Compute the 2D cross product of @p lhs and @p rhs
     *
     * This is not truely a 2D cross product. It is the cross product of the corresponding 3D 
     * vectors with 0 in the z coordinate.
     * 
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The 2D cross product of @p lhs and @p rhs 
     */
    template<typename T>
    inline T const cross(vec2<T> const& lhs, vec2<T> const& rhs)
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    /**
     * @brief Compute the 3D cross product of @p lhs and @p rhs
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The 3D cross product of @p lhs and @p rhs
     */
    template<typename T>
    inline vec3<T> const cross(vec3<T> const& lhs, vec3<T> const& rhs)
    {
        return vec3<T>
        (
            cross(vec2<T>(lhs.y, lhs.z), vec2<T>(rhs.y, rhs.z)),
            -cross(vec2<T>(lhs.x, lhs.z), vec2<T>(rhs.x, rhs.z)),
            cross(vec2<T>(lhs.x, lhs.y), vec2<T>(rhs.x, rhs.y))
        );
    }

    /** 
     * @brief Compute the orientation of @p p, @p q, and @p r
     *
     * The orientation is determined based on the sign of the return value
     *    * + => counterclockwise
     *    * 0 => colinear
     *    * - => clockwise
     * 
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] p
     * @param [in] q
     * @param [in] r
     * @return The orientation of @p p, @p q, and @p r
     */
    template<typename T>
    inline T orientation(vec2<T> const& p, vec2<T> const& q, vec2<T> const& r)
    {
        return cross(q - p, r - p);
    }

    /** 
     * @brief Compute the hadamard product of @p lhs and @p rhs
     * 
     * The hadamard product is element-wise multiplication of vectors.
     * 
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return The hadamard product of @p lhs and @p rhs
     */
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

    /** 
     * @brief Write the vector @p rhs to the std::ostream @p s
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in,out] s
     * @param [in] rhs
     * @return A reference to @p s
     */
    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& s, vec<T, N> const& rhs)
    {
        s << "[ " << rhs[0];
        for (size_t i = 1; i < N; ++i)
        {
            s << ", " << rhs[i];
        }
        s << " ]";
        return s;
    }

} // stf::math

namespace std
{
    /**
     * @brief Templated class that can compute the has of a vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct hash<stf::math::vec<T, N>>
    {
        
        /**
         * @brief Compute the hash of a vector
         * @param [in] lhs 
         * @return The hash of @p lhs
         */
        size_t operator()(stf::math::vec<T, N> const& lhs) const
        {
            std::hash<T> hasher;
            size_t result = 17;
            for (size_t i = 0; i < N; ++i)
            {
                result = result * 23 + hasher(lhs[i]);
            }
            return result;
        }
    };

} // std