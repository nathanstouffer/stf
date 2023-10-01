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

        mat() { identitied(); }
        mat(T value) 
        {
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = value;
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

        inline mat& identitied()
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

        inline mat transposed() const
        {
            return mat(*this).transpose();
        }

        inline void col_major(T fill[N * N]) const
        {
            for (size_t i = 0; i < D; ++i)
            {
                fill[i] = values[i];
            }
        }

        inline void row_major(T fill[N * N]) const
        {
            return transposed().col_major(fill);
        }

    public:

        static mat identity()
        {
            return mat();
        }

    };

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


} // math
} // stf