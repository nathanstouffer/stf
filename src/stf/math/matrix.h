#pragma once

#include "vector.h"

namespace stf {
namespace math {

    template<typename T, size_t N>
    struct mat
    {

        struct col_proxy
        {

            col_proxy(mat& _m, size_t _c) : m(_m), c(_c) {}

            T const& operator[](size_t i) const { return m.values[c * N + i]; }
            T& operator[](size_t i) { return m.values[c * N + i]; }
        
            operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t i = 0; i < N; ++i) { vec[i] = (*this)[i]; }
                return vec;
            }

        private:

            mat& m;
            size_t c;

        };

        struct row_proxy
        {

            row_proxy(mat& _m, size_t _r) : m(_m), r(_r) {}

            T const& operator[](size_t j) const { return m.values[r + j * N]; }
            T& operator[](size_t j) { return m.values[r + j * N]; }
        
            operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t i = 0; i < N; ++i) { vec[i] = (*this)[i]; }
                return vec;
            }

        private:

            mat& m;
            size_t r;

        };

        static size_t constexpr D = N * N;

        // values defining this matrix (stored in column major format)
        T values[N * N];

        mat() : mat(0) {}
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

        mat<T, N>& transpose()
        {
            // TODO write this method by swapping the values in place
            T transposed[N * N];
            for (size_t i = 0; i < N; ++i)          // iterate over columns
            {
                for (size_t j = 0; j < N; ++j)      // iterate over rows
                {
                    transposed[j][i] = (*this)[i][j];
                }
            }

            // copy to values
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = transposed[i];
            }
        }

        mat<T, N> transposed() const
        {
            return mat<T, N>(*this).transpose();
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

    };

} // math
} // stf