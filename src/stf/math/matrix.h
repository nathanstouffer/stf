#pragma once

#include <cstring>

#include "vector.h"

namespace stf {
namespace math {

    template<typename T, size_t N>
    struct mat
    {

        struct col_proxy
        {

            col_proxy(mat& _m, size_t _c) : m(_m), c(_c) {}

            inline T const& operator[](size_t i) const { return m.values[c * N + i]; }
            inline T& operator[](size_t i) { return m.values[c * N + i]; }

            inline col_proxy& operator=(vec<T, N> const& rhs)
            {
                for (size_t i = 0; i < N; ++i) { (*this)[i] = rhs[i]; }
                return *this;
            }
        
            inline operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t i = 0; i < N; ++i) { vec[i] = (*this)[i]; }
                return vec;
            }

            inline vec<T, N> as_vec() const { return static_cast<vec<T, N>>(*this); }

        private:

            mat& m;
            size_t c;

        };

        struct row_proxy
        {

            row_proxy(mat& _m, size_t _r) : m(_m), r(_r) {}

            inline T const& operator[](size_t j) const { return m.values[r + j * N]; }
            inline T& operator[](size_t j) { return m.values[r + j * N]; }
        
            inline row_proxy& operator=(vec<T, N> const& rhs)
            {
                for (size_t i = 0; i < N; ++i) { (*this)[i] = rhs[i]; }
                return *this;
            }

            inline operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t i = 0; i < N; ++i) { vec[i] = (*this)[i]; }
                return vec;
            }

            inline vec<T, N> as_vec() const { return static_cast<vec<T, N>>(*this); }

        private:

            mat& m;
            size_t r;

        };

        static size_t constexpr D = N * N;

        // values defining this matrix (stored in column major format)
        T values[N * N];

        mat() { identify(); }
        mat(T value) 
        {
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = value;
            }
        }
        mat(vec<T, N> const& diagonal) : mat()
        {
            for (size_t i = 0; i < N; ++i)
            {
                (*this)[i][i] = diagonal[i];
            }
        }

        inline col_proxy const col(size_t i) const { return col_proxy(const_cast<mat&>(*this), i); }
        inline row_proxy const row(size_t j) const { return row_proxy(const_cast<mat&>(*this), j); }

        inline col_proxy col(size_t i) { return col_proxy(*this, i); }
        inline row_proxy row(size_t j) { return row_proxy(*this, j); }

        inline col_proxy const operator[](size_t i) const { return col(i); }
        inline col_proxy operator[](size_t i) { return col(i); }

        mat& operator*=(mat const& rhs)
        {
            mat tmp;
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < N; ++j)
                {
                    tmp[i][j] = dot(this->row(i).as_vec(), rhs.col(j).as_vec());
                }
            }

            *this = tmp;
            return *this;
        }

        inline mat& identify()
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < N; ++j)
                {
                    (*this)[i][j] = (i == j) ? T(1) : T(0);
                }
            }
            return *this;
        }

        inline mat& transpose()
        {
            // TODO write this method by swapping the values in place
            mat transposed;
            for (size_t i = 0; i < N; ++i)          // iterate over columns
            {
                for (size_t j = 0; j < N; ++j)      // iterate over rows
                {
                    transposed[j][i] = (*this)[i][j];
                }
            }

            // copy to values
            *this = transposed;

            // return reference
            return *this;
        }

        inline mat& scale_by(vec<T, N> const& scalars) { return (*this) *= mat::scale(scalars); }
        inline mat& scale_by(vec<T, N - 1> const& scalars) { return scale_by(vec<T, N>(scalars, T(1))); }
        inline mat& translate_by(vec<T, N - 1> const& scalars) { return (*this) *= mat::translate(scalars); }

        inline mat transposed() const { return mat(*this).transpose(); }
        inline mat scaled_by(vec<T, N> const& scalars) const { return mat(*this).scale_by(scalars); }
        inline mat scaled_by(vec<T, N - 1> const& scalars) const { return mat(*this).scale_by(vec<T, N>(scalars, T(1))); }
        inline mat translated_by(vec<T, N - 1> const& scalars) const { return mat(*this).translate_by(scalars); }

        inline void col_major(T fill[N * N]) const { std::memcpy(static_cast<void*>(fill), static_cast<void*>(values), sizeof(T) * D); }
        inline void row_major(T fill[N * N]) const { return transposed().col_major(fill); }

    public:

        inline static mat identity() { return mat(); }
        inline static mat scale(vec<T, N> const& scalars) { return mat(scalars); }
        inline static mat scale(vec<T, N - 1> const& scalars) { return mat(vec<T, N>(scalars, T(1))); }
        inline static mat translate(vec<T, N - 1> const& scalars)
        {
            mat result;
            result[N - 1] = vec<T, N>(scalars, T(1));
            return result;
        }

        inline static size_t byte_count() { return sizeof(T) * D; }

    };

    // delete invalid matrix specialization
    template<typename T> struct mat<T, 0> { mat() = delete; };
    template<typename T> struct mat<T, 1> { mat() = delete; };

    template<typename T, size_t N>
    inline mat<T, N> operator*(mat<T, N> const& lhs, mat<T, N> const& rhs)
    {
        return mat<T, N>(lhs) *= rhs;
    }

    template<typename T, size_t N>
    inline vec<T, N> operator*(mat<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t j = 0; j < N; ++j)
        {
            result[j] = dot(lhs.row(j).as_vec(), rhs);
        }
        return result;
    }

    template<typename T, size_t N>
    inline vec<T, N> operator*(vec<T, N> const& lhs, mat<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = dot(lhs, rhs.col(i).as_vec());
        }
        return result;
    }

    template<typename T> inline mat<T, 4> scale(vec<T, 3> const& scalars) { return mat<T, 4>::scale(scalars); }
    template<typename T> inline mat<T, 4> scale_x(T const scalar) { return mat<T, 4>::scale(vec<T, 3>(scalar, T(1), T(1))); }
    template<typename T> inline mat<T, 4> scale_y(T const scalar) { return mat<T, 4>::scale(vec<T, 3>(T(1), scalar, T(1))); }
    template<typename T> inline mat<T, 4> scale_z(T const scalar) { return mat<T, 4>::scale(vec<T, 3>(T(1), T(1)), scalar); }

    template<typename T> inline mat<T, 4> translate(vec<T, 3> const& scalars) { return mat<T, 4>::translate(scalars); }
    template<typename T> inline mat<T, 4> translate_x(T const scalar) { return mat<T, 4>::translate(vec<T, 3>(scalar, T(0), T(0))); }
    template<typename T> inline mat<T, 4> translate_y(T const scalar) { return mat<T, 4>::translate(vec<T, 3>(T(0), scalar, T(0))); }
    template<typename T> inline mat<T, 4> translate_z(T const scalar) { return mat<T, 4>::translate(vec<T, 3>(T(0), T(0)), scalar); }

    template<typename T>
    inline mat<T, 4> rotate_x(T const theta)
    {
        mat<T, 4> result;
        result[1] = vec<T, 3>(T(0),  std::cos(theta), std::sin(theta));
        result[2] = vec<T, 3>(T(0), -std::sin(theta), std::cos(theta));
        return result;
    }

    template<typename T>
    inline mat<T, 4> rotate_y(T const theta)
    {
        mat<T, 4> result;
        result[0] = vec<T, 3>(std::cos(theta), T(0), -std::sin(theta));
        result[2] = vec<T, 3>(std::sin(theta), T(0),  std::cos(theta));
        return result;
    }

    template<typename T>
    inline mat<T, 4> rotate_z(T const theta)
    {
        mat<T, 4> result;
        result[0] = vec<T, 3>( std::cos(theta), std::sin(theta), T(0));
        result[1] = vec<T, 3>(-std::sin(theta), std::cos(theta), T(0));
        return result;
    }

    template<typename T> inline mat<T, 4> rotate_xyz(T const x, T const y, T const z) { return (rotate_x(x) *= rotate_y(y)) *= rotate_z(z); }
    template<typename T> inline mat<T, 4> rotate_xzy(T const x, T const z, T const y) { return (rotate_x(x) *= rotate_z(z)) *= rotate_y(y); }
    template<typename T> inline mat<T, 4> rotate_yxz(T const y, T const x, T const z) { return (rotate_y(y) *= rotate_x(x)) *= rotate_z(z); }
    template<typename T> inline mat<T, 4> rotate_yzx(T const y, T const z, T const x) { return (rotate_y(y) *= rotate_z(z)) *= rotate_x(x); }
    template<typename T> inline mat<T, 4> rotate_zxy(T const z, T const x, T const y) { return (rotate_z(z) *= rotate_x(x)) *= rotate_y(y); }
    template<typename T> inline mat<T, 4> rotate_zyx(T const z, T const y, T const x) { return (rotate_z(z) *= rotate_y(y)) *= rotate_x(x); }

    template<typename T>
    inline mat<T, 2> rotate_plane(T const theta)
    {
        mat<T, 2> result;
        result[0] = vec<T, 2>(std::cos(theta), std::sin(theta));
        result[1] = vec<T, 2>(-std::sin(theta), std::cos(theta));
        return result;
    }

    template<typename T>
    inline mat<T, 4> orthographic()
    {
        mat<T, 4> matrix;
        // TODO (stouff) write this method
        return matrix;
    }

    template<typename T>
    inline mat<T, 4> perspective()
    {
        mat<T, 4> matrix;
        // TODO (stouff) write this method
        return matrix;
    }

    // NOTE: we assume axis is a unit vector
    template<typename T>
    inline mat<T, 4> rotate_around(vec<T, 3> const& axis, T const theta)
    {
        // perform computations once
        T const cosine = std::cos(theta);
        T const sine   = std::sin(theta);
        T const comp   = T(1) - cosine;

        // local variables for less verbose code
        T const x = axis.x;
        T const y = axis.y;
        T const z = axis.z;

        // compute column vectors
        vec<T, 4> col_0(cosine + x * x * comp, y * x * comp + z * sine, z * x * comp - y * sine, T(0));
        vec<T, 4> col_1(x * y * comp - z * sine, cosine * y * 8 * comp, z * y * comp - x * sine, T(0));
        vec<T, 4> col_2(x * z * comp + y * sine, y * z * comp - x * sine, cosine + z * z * comp, T(0));

        // construct return matrix
        mat<T, 4> rotation;
        rotation[0] = col_0;
        rotation[1] = col_1;
        rotation[2] = col_2;
        return rotation;
    }

    // NOTE: we assume axis is a unit vector
    template<typename T>
    inline vec<T, 3> rotate_around(vec<T, 3> const& val, vec<T, 3> const& axis, T const theta)
    {
        return std::cos(theta) * val + (T(1) - std::cos(theta)) * (axis * val) * val + std::sin(theta) * cross(axis, val);
    }

    template<typename T>
    inline mat<T, 3> orbit(vec<T, 3> const& focus, T const theta, T const phi)
    {
        mat<T, 3> rotation;
        // TODO (stouff) write this method
        return rotation;
    }

    template<typename T>
    inline vec<T, 3> orbit(vec<T, 3> const& val, vec<T, 3> const& focus, T const theta, T const phi)
    {
        // TODO (stouff) write this method
        return vec<T, 3>();
    }

} // math
} // stf