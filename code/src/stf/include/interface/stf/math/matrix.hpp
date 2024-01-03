#pragma once

#include <cstring>

#include "stf/math/raw.hpp"
#include "stf/math/vector.hpp"

namespace stf::math
{

    template<typename T, size_t N>
    struct mtx
    {

        struct col_proxy
        {

            col_proxy(mtx& _m, size_t _c) : m(_m), c(_c) {}

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

            mtx& m;
            size_t c;

        };

        struct row_proxy
        {

            row_proxy(mtx& _m, size_t _r) : m(_m), r(_r) {}

            inline T const& operator[](size_t j) const { return m.values[r + j * N]; }
            inline T& operator[](size_t j) { return m.values[r + j * N]; }
        
            inline row_proxy& operator=(vec<T, N> const& rhs)
            {
                for (size_t j = 0; j < N; ++j) { (*this)[j] = rhs[j]; }
                return *this;
            }

            inline operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t j = 0; j < N; ++j) { vec[j] = (*this)[j]; }
                return vec;
            }

            inline vec<T, N> as_vec() const { return static_cast<vec<T, N>>(*this); }

        private:

            mtx& m;
            size_t r;

        };

        static size_t constexpr D = N * N;

        // values defining this matrix (stored in column major formtx)
        T values[N * N];

        mtx() { identify(); }
        mtx(T value) 
        {
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = value;
            }
        }
        mtx(vec<T, N> const& diagonal) : mtx()
        {
            for (size_t i = 0; i < N; ++i)
            {
                (*this)[i][i] = diagonal[i];
            }
        }

        inline col_proxy const col(size_t j) const { return col_proxy(const_cast<mtx&>(*this), j); }
        inline row_proxy const row(size_t i) const { return row_proxy(const_cast<mtx&>(*this), i); }

        inline col_proxy col(size_t j) { return col_proxy(*this, j); }
        inline row_proxy row(size_t i) { return row_proxy(*this, i); }

        inline row_proxy const operator[](size_t i) const { return row(i); }
        inline row_proxy operator[](size_t i) { return row(i); }

        mtx& operator*=(mtx const& rhs)
        {
            mtx tmp;
            for (size_t i = 0; i < N; ++i)          // iterate over rows
            {
                for (size_t j = 0; j < N; ++j)      // iterate over columns
                {
                    tmp[i][j] = dot(row(i).as_vec(), rhs.col(j).as_vec());
                }
            }

            *this = tmp;
            return *this;
        }

        inline mtx& identify()
        {
            for (size_t i = 0; i < N; ++i)          // iterate over rows
            {
                for (size_t j = 0; j < N; ++j)      // iterate over columns
                {
                    (*this)[i][j] = (i == j) ? T(1) : T(0);
                }
            }
            return *this;
        }

        inline mtx& transpose()
        {
            // TODO write this method by swapping the values in place
            mtx transposed;
            for (size_t i = 0; i < N; ++i)          // iterate over rows
            {
                for (size_t j = 0; j < N; ++j)      // iterate over columns
                {
                    transposed[j][i] = (*this)[i][j];
                }
            }

            // copy to values
            *this = transposed;

            // return reference
            return *this;
        }

        inline mtx& scale_by(vec<T, N> const& scalars) { return (*this) *= mtx::scale(scalars); }
        inline mtx& scale_by(vec<T, N - 1> const& scalars) { return scale_by(vec<T, N>(scalars, T(1))); }
        inline mtx& translate_by(vec<T, N - 1> const& scalars) { return (*this) *= mtx::translate(scalars); }

        inline mtx transposed() const { return mtx(*this).transpose(); }
        inline mtx scaled_by(vec<T, N> const& scalars) const { return mtx(*this).scale_by(scalars); }
        inline mtx scaled_by(vec<T, N - 1> const& scalars) const { return mtx(*this).scale_by(vec<T, N>(scalars, T(1))); }
        inline mtx translated_by(vec<T, N - 1> const& scalars) const { return mtx(*this).translate_by(scalars); }

        inline void col_major(T fill[N * N]) const { std::memcpy(static_cast<void*>(fill), static_cast<void*>(values), sizeof(T) * D); }
        inline void row_major(T fill[N * N]) const { return transposed().col_major(fill); }

        template<typename U>
        mtx<U, N * N> as() const
        {
            mtx<U, D> result;
            raw::as<T, U, N * N>(values, result.values);
            return result;
        }


    public:

        inline static mtx identity() { return mtx(); }
        inline static mtx scale(vec<T, N> const& scalars) { return mtx(scalars); }
        inline static mtx scale(vec<T, N - 1> const& scalars) { return mtx(vec<T, N>(scalars, T(1))); }
        inline static mtx translate(vec<T, N - 1> const& scalars)
        {
            mtx result;
            for (size_t i = 0; i < N - 1; ++i) { result[i][N - 1] = scalars[i]; }
            return result;
        }

        inline static size_t byte_count() { return sizeof(T) * D; }

    };

    // delete invalid matrix specialization
    template<typename T> struct mtx<T, 0> { mtx() = delete; };
    template<typename T> struct mtx<T, 1> { mtx() = delete; };

    // type aliases for ease of use
    template<typename T> using mtx2 = mtx<T, 2>;
    template<typename T> using mtx3 = mtx<T, 3>;
    template<typename T> using mtx4 = mtx<T, 4>;

    template<typename T, size_t N>
    inline mtx<T, N> operator*(mtx<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        return mtx<T, N>(lhs) *= rhs;
    }

    template<typename T, size_t N>
    inline vec<T, N> operator*(mtx<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t j = 0; j < N; ++j)
        {
            result[j] = dot(lhs.row(j).as_vec(), rhs);
        }
        return result;
    }

    template<typename T, size_t N>
    inline vec<T, N> operator*(vec<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = dot(lhs, rhs.col(i).as_vec());
        }
        return result;
    }

    template<typename T> inline mtx4<T> scale(vec<T, 3> const& scalars) { return mtx4<T>::scale(scalars); }
    template<typename T> inline mtx4<T> scale_x(T const scalar) { return mtx4<T>::scale(vec<T, 3>(scalar, T(1), T(1))); }
    template<typename T> inline mtx4<T> scale_y(T const scalar) { return mtx4<T>::scale(vec<T, 3>(T(1), scalar, T(1))); }
    template<typename T> inline mtx4<T> scale_z(T const scalar) { return mtx4<T>::scale(vec<T, 3>(T(1), T(1)), scalar); }

    template<typename T> inline mtx4<T> translate(vec<T, 3> const& scalars) { return mtx4<T>::translate(scalars); }
    template<typename T> inline mtx4<T> translate_x(T const scalar) { return mtx4<T>::translate(vec<T, 3>(scalar, T(0), T(0))); }
    template<typename T> inline mtx4<T> translate_y(T const scalar) { return mtx4<T>::translate(vec<T, 3>(T(0), scalar, T(0))); }
    template<typename T> inline mtx4<T> translate_z(T const scalar) { return mtx4<T>::translate(vec<T, 3>(T(0), T(0)), scalar); }

    template<typename T>
    inline mtx4<T> rotate_x(T const theta)
    {
        mtx4<T> result;
        result.row(1) = vec<T, 3>(T(0), std::cos(theta), -std::sin(theta));
        result.row(2) = vec<T, 3>(T(0), std::sin(theta),  std::cos(theta));
        return result;
    }

    template<typename T>
    inline mtx4<T> rotate_y(T const theta)
    {
        mtx4<T> result;
        result.row(0) = vec<T, 3>( std::cos(theta), T(0), std::sin(theta));
        result.row(2) = vec<T, 3>(-std::sin(theta), T(0), std::cos(theta));
        return result;
    }

    template<typename T>
    inline mtx4<T> rotate_z(T const theta)
    {
        mtx4<T> result;
        result.row(0) = vec<T, 3>(std::cos(theta), -std::sin(theta), T(0));
        result.row(1) = vec<T, 3>(std::sin(theta),  std::cos(theta), T(0));
        return result;
    }

    template<typename T> inline mtx4<T> rotate_xyz(T const x, T const y, T const z) { return (rotate_x(x) *= rotate_y(y)) *= rotate_z(z); }
    template<typename T> inline mtx4<T> rotate_xzy(T const x, T const z, T const y) { return (rotate_x(x) *= rotate_z(z)) *= rotate_y(y); }
    template<typename T> inline mtx4<T> rotate_yxz(T const y, T const x, T const z) { return (rotate_y(y) *= rotate_x(x)) *= rotate_z(z); }
    template<typename T> inline mtx4<T> rotate_yzx(T const y, T const z, T const x) { return (rotate_y(y) *= rotate_z(z)) *= rotate_x(x); }
    template<typename T> inline mtx4<T> rotate_zxy(T const z, T const x, T const y) { return (rotate_z(z) *= rotate_x(x)) *= rotate_y(y); }
    template<typename T> inline mtx4<T> rotate_zyx(T const z, T const y, T const x) { return (rotate_z(z) *= rotate_y(y)) *= rotate_x(x); }

    template<typename T>
    inline mtx<T, 2> rotate_plane(T const theta)
    {
        mtx<T, 2> result;
        result.row(0) = vec<T, 2>(std::cos(theta), -std::sin(theta));
        result.row(1) = vec<T, 2>(std::sin(theta),  std::cos(theta));
        return result;
    }

    template<typename T>
    inline mtx4<T> orthographic(T const l, T const r, T const b, T const t, T const n, T const f)
    {
        vec<T, 3> scalars(T(2) / (r - l), T(2) / (t - b), -T(2) / (f - n));
        vec<T, 3> translators(-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n));
        return mtx4<T>::scale(scalars) * mtx4<T>::translate(translators);
    }

    template<typename T>
    inline mtx4<T> perspective(T const fov, T const aspect, T const near, T const far)
    {
        T y_scale = T(1.0) / std::tan(T(0.5) * fov);
        T x_scale = y_scale / aspect;
        mtx4<T> result;
        result[0][0] = x_scale;
        result[1][1] = y_scale;
        result[2][2] = far / (near - far);
        result[2][3] = near * far / (near - far);
        result[3][2] = -1;
        return result;
    }

    // NOTE: we assume axis is a unit vector
    template<typename T>
    inline mtx4<T> rotate(vec<T, 3> const& axis, T const theta)
    {
        // perform computations once
        T const cosine = std::cos(theta);
        T const sine   = std::sin(theta);
        T const comp   = T(1) - cosine;     // complement

        // local variables for less verbose code
        T const x = axis.x;
        T const y = axis.y;
        T const z = axis.z;

        // compute row vectors
        vec<T, 4> row_0(cosine + x * x * comp, x * y * comp - z * sine, x * z * comp + y * sine, T(0));
        vec<T, 4> row_1(y * x * comp + z * sine, cosine + y * y * comp, y * z * comp - x * sine, T(0));
        vec<T, 4> row_2(z * x * comp - y * sine, z * y * comp + x * sine, cosine + z * z * comp, T(0));

        // construct return matrix
        mtx4<T> rotation;
        rotation.row(0) = row_0;
        rotation.row(1) = row_1;
        rotation.row(2) = row_2;
        return rotation;
    }

    // NOTE: we assume angles are from the perspective of the focus point and that right is a unit vector
    template<typename T>
    inline mtx4<T> orbit(vec<T, 3> const& focus, vec<T, 3> const& right, T const delta_phi, T const delta_theta)
    {
        mtx4<T> translate = mtx4<T>::translate(-focus);
        mtx4<T> pitch = rotate(right, delta_phi);
        mtx4<T> yaw = rotate(vec<T, 3>(0, 0, 1), delta_theta);
        mtx4<T> invert_translation = mtx4<T>::translate(focus);
        return invert_translation * yaw * pitch * translate;
    }

    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& s, mtx<T, N> const& rhs)
    {
        s << rhs.row(0).as_vec();
        for (size_t i = 1; i < N; ++i)
        {
            s << std::endl << rhs.row(i).as_vec();
        }
        return s;
    }

} // stf::math