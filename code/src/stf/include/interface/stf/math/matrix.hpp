#pragma once

#include <cstring>

#include "stf/math/raw.hpp"
#include "stf/math/vector.hpp"

/**
 * @file matrix.hpp
 * @brief A file containing a templated matrix class along with associated functions
 */

namespace stf::math
{
    /**
     * @brief A square matrix class templated on number type and dimension
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct mtx final
    {

        /**
         * @brief A proxy class that gives access to a single column of a @ref mtx
         */
        struct col_proxy
        {

            /**
             * @brief Construct from a @ref mtx reference and a column index
             * @param [in] _m 
             * @param [in] _c 
             */
            col_proxy(mtx& _m, size_t _c) : m(_m), c(_c) {}

            /**
             * @brief Const access to a single scalar in the column
             * @param [in] i The index of the row
             * @return A const reference to the scalar
             */
            inline T const& operator[](size_t i) const { return m.values[c * N + i]; }

            /**
             * @brief Access to a single scalar in the column
             * @param [in] i The index of the row
             * @return A reference to the scalar
             */
            inline T& operator[](size_t i) { return m.values[c * N + i]; }

            /**
             * @brief Assignment operator
             * @param [in] rhs 
             * @return A reference to @p this
             */
            inline col_proxy& operator=(vec<T, N> const& rhs)
            {
                for (size_t i = 0; i < N; ++i) { (*this)[i] = rhs[i]; }
                return *this;
            }
        
            /**
             * @brief Cast a @ref col_proxy to a @ref vec
             */
            inline operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t i = 0; i < N; ++i) { vec[i] = (*this)[i]; }
                return vec;
            }

            /**
             * @brief Cast a @ref col_proxy to a @ref vec
             * @return The column proxy as a vector
             */
            inline vec<T, N> as_vec() const { return static_cast<vec<T, N>>(*this); }

        private:

            mtx& m;
            size_t c;

        };

        /**
         * @brief A proxy class that gives access to a single row of a @ref mtx
         */
        struct row_proxy
        {

            /**
             * @brief Construct from a @ref mtx reference and a row index
             * @param [in] _m
             * @param [in] _r
             */
            row_proxy(mtx& _m, size_t _r) : m(_m), r(_r) {}

            /**
             * @brief Const access to a single scalar in the row
             * @param [in] j The index of the column
             * @return A const reference to the scalar
             */
            inline T const& operator[](size_t j) const { return m.values[r + j * N]; }

            /**
             * @brief Access to a single scalar in the rwo
             * @param [in] j The index of the column
             * @return A reference to the scalar
             */
            inline T& operator[](size_t j) { return m.values[r + j * N]; }
        
            /**
             * @brief Assignment operator
             * @param [in] rhs
             * @return A reference to @p this
             */
            inline row_proxy& operator=(vec<T, N> const& rhs)
            {
                for (size_t j = 0; j < N; ++j) { (*this)[j] = rhs[j]; }
                return *this;
            }

            /**
             * @brief Cast a @ref row_proxy to a @ref vec
             */
            inline operator vec<T, N>() const
            {
                vec<T, N> vec;
                for (size_t j = 0; j < N; ++j) { vec[j] = (*this)[j]; }
                return vec;
            }

            /**
             * @brief Cast a @ref row_proxy to a @ref vec
             * @return The row proxy as a vector
             */
            inline vec<T, N> as_vec() const { return static_cast<vec<T, N>>(*this); }

        private:

            mtx& m;
            size_t r;

        };

        /**
         * @brief The number of scalars stored in the matrix
         */
        static size_t constexpr D = N * N;

        /**
         * @brief The scalars defining this matrix
         * @note Stored in column-major form
         */
        T values[N * N];

        /**
         * @brief Default constructor -- intializes to the identity matrix
         */
        mtx() { identify(); }

        /**
         * @brief Construct from a single scalar -- initializes all scalars to @p value
         * @param [in] value 
         */
        explicit mtx(T const value) 
        {
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = value;
            }
        }

        /**
         * @brief Construct from an N-dimensional vector -- intializes the diagonal to the value of the vector
         * @param [in] diagonal 
         */
        explicit mtx(vec<T, N> const& diagonal) : mtx()
        {
            for (size_t i = 0; i < N; ++i)
            {
                (*this)[i][i] = diagonal[i];
            }
        }

        /**
         * @brief Construct from an NxN-dimensional vector -- an explicit column-major initialization of every entry in the matrix
         * @param [in] values
         */
        explicit mtx(vec<T, D> const& _values) : mtx()
        {
            for (size_t i = 0; i < D; ++i)
            {
                values[i] = _values[i];
            }
        }

        /**
         * @brief Const access to a single column of the matrix
         * @param [in] j The index of the column
         * @return A proxy class that gives const access to the column
         */
        inline col_proxy const col(size_t const j) const { return col_proxy(const_cast<mtx&>(*this), j); }
        
        /**
         * @brief Access to a single column of the matrix
         * @param [in] j The index of the column
         * @return A proxy class that gives access to the column
         */
        inline col_proxy col(size_t const j) { return col_proxy(*this, j); }

        /**
         * @brief Const access to a single row of the matrix
         * @param [in] i The index of the row
         * @return A proxy class that gives const access to the row
         */
        inline row_proxy const row(size_t const i) const { return row_proxy(const_cast<mtx&>(*this), i); }

        /**
         * @brief Access to a single row of the matrix
         * @param [in] i The index of the row
         * @return A proxy class that gives access to the row
         */
        inline row_proxy row(size_t const i) { return row_proxy(*this, i); }

        /**
         * @brief Const access to a single row of the matrix
         * @param [in] i The index of the row
         * @return A proxy class that gives const access to the row
         */
        inline row_proxy const operator[](size_t const i) const { return row(i); }

        /**
         * @brief Access to a single row of the matrix
         * @param [in] i The index of the row
         * @return A proxy class that gives access to the row
         */
        inline row_proxy operator[](size_t const i) { return row(i); }

        /**
         * @brief Multiply a matrix by a scalar in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        inline mtx& operator*=(T const scalar)
        {
            for (size_t d = 0; d < D; ++d)
            {
                values[d] *= scalar;
            }
            return *this;
        }

        /**
         * @brief Multiply a matrix by a matrix in place
         * @param [in] rhs 
         * @return A reference to @p this
         */
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

        /**
         * @brief Set a matrix to the identity matrix
         * @return A reference to @p this 
         */
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

        /**
         * @brief Transpose a matrix
         * @return A reference to @p this
         */
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

        /**
         * @brief Compute the transpose of a matrix
         * @return The transpose of @p this
         */
        inline mtx transposed() const { return mtx(*this).transpose(); }

        /**
         * @brief Multiply a matrix by a scale matrix in place
         * @param [in] scalars The scalars defining the scale matrix
         * @return A reference to @p this
         */
        inline mtx& scale_by(vec<T, N> const& scalars) { return (*this) *= mtx::scale(scalars); }

        /**
         * @brief Multiply a matrix by a scale matrix
         * @param [in] scalars The scalars defining the scale matrix
         * @return The resulting transformation matrix
         */
        inline mtx scaled_by(vec<T, N> const& scalars) const { return mtx(*this).scale_by(scalars); }

        /**
         * @brief Multiply a matrix by a scale matrix in place
         * @param [in] scalars The scalars defining the scale matrix -- sets the Nth scalar to 1
         * @return A reference to @p this
         */
        inline mtx& scale_by(vec<T, N - 1> const& scalars) { return scale_by(vec<T, N>(scalars, T(1))); }

        /**
         * @brief Multiply a matrix by a scale matrix
         * @param [in] scalars The scalars defining the scale matrix -- sets the Nth scalar to 1
         * @return The resulting transformation matrix
         */
        inline mtx scaled_by(vec<T, N - 1> const& scalars) const { return mtx(*this).scale_by(vec<T, N>(scalars, T(1))); }

        /**
         * @brief Multiply a matrix by a translation matrix in place
         * @param [in] scalars The scalars definining the translation matrix
         * @return A reference to @p this 
         */
        inline mtx& translate_by(vec<T, N - 1> const& scalars) { return (*this) *= mtx::translate(scalars); }

        /**
         * @brief Multiply a matrix by a translation matrix
         * @param [in] scalars The scalars definining the translation matrix
         * @return The resulting transformation matrix
         */
        inline mtx translated_by(vec<T, N - 1> const& scalars) const { return mtx(*this).translate_by(scalars); }

        /**
         * @brief Compute a mtx that is the top left section of a matrix
         * @return The top left section of @p this
         */
        mtx<T, N - 1> prefix() const
        {
            mtx<T, N - 1> matrix = mtx<T, N - 1>();
            for (size_t i = 0; i < N - 1; ++i)
            {
                matrix[i] = math::prefix(row(i).as_vec());
            }
            return matrix;
        }

        /**
         * @brief Fill a raw array with scalars of the matrix in column-major form
         * @param [out] fill 
         */
        inline void col_major(T fill[N * N]) const { std::memcpy(static_cast<void*>(fill), static_cast<void*>(values), sizeof(T) * D); }

        /**
         * @brief Fill a raw array with scalars of the matrix in row-major form
         * @param [out] fill
         */
        inline void row_major(T fill[N * N]) const { return transposed().col_major(fill); }

        /**
         * @brief Cast a matrix to a different precision
         * @tparam U Destination number type (eg float)
         * @return @p this casted to the precision of @p U
         */
        template<typename U>
        mtx<U, N * N> as() const
        {
            mtx<U, D> result;
            raw::as<T, U, N * N>(values, result.values);
            return result;
        }


    public:

        /**
         * @brief Compute the identity matrix
         * @return The identity matrix
         */
        inline static mtx identity() { return mtx(); }

        /**
         * @brief Compute a scale matrix
         * @param [in] scalars The scalars defining the scale matrix
         * @return A scale matrix
         */
        inline static mtx scale(vec<T, N> const& scalars) { return mtx(scalars); }

        /**
         * @brief Compute a scale matrix
         * @param [in] scalars The scalars defining the scale matrix -- sets the Nth scalar to 1
         * @return A scale matrix
         */
        inline static mtx scale(vec<T, N - 1> const& scalars) { return mtx(vec<T, N>(scalars, T(1))); }

        /**
         * @brief Compute a translation matrix
         * @param [in] scalars The scalars defining the translation matrix
         * @return A translation matrix
         */
        inline static mtx translate(vec<T, N - 1> const& scalars)
        {
            mtx result;
            for (size_t i = 0; i < N - 1; ++i) { result[i][N - 1] = scalars[i]; }
            return result;
        }

        /**
         * @brief Compute the number of bytes allocated by matrix
         * @return The byte count
         */
        inline static size_t byte_count() { return sizeof(T) * D; }

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid matrix specializations
     */
    template<typename T> struct mtx<T, 0> { mtx() = delete; };
    template<typename T> struct mtx<T, 1> { mtx() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2x2 matrix
     * @tparam T Number type (eg float)
     */
    template<typename T> using mtx2 = mtx<T, 2>;

    /**
     * @brief Type alias for a 3x3 matrix
     * @tparam T Number type (eg float)
     */
    template<typename T> using mtx3 = mtx<T, 3>;

    /**
     * @brief Type alias for a 4x4 matrix
     * @tparam T Number type (eg float)
     */
    template<typename T> using mtx4 = mtx<T, 4>;

    /**
     * @brief Compute whether @p lhs is approximately equal to @p rhs (uses constants<T>::tol as epsilon)
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs and @p rhs are approximately equal
     */
    template<typename T, size_t N>
    inline bool const operator==(mtx<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        vec<T, N * N> lhs_as_vec = vec<T, N * N>(lhs.values);
        vec<T, N * N> rhs_as_vec = vec<T, N * N>(rhs.values);
        return equ(lhs_as_vec, rhs_as_vec, constants<T>::tol);
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
    inline bool const operator!=(mtx<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Compute the product of two matrices
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs 
     * @param [in] rhs 
     * @return The matrix result of the product between @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline mtx<T, N> const operator*(mtx<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        return mtx<T, N>(lhs) *= rhs;
    }

    /**
     * @brief Compute the product of a matrix with a column vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs A matrix
     * @param [in] rhs A column vector
     * @return The column vector result of the product between @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator*(mtx<T, N> const& lhs, vec<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t j = 0; j < N; ++j)
        {
            result[j] = dot(lhs.row(j).as_vec(), rhs);
        }
        return result;
    }

    /**
     * @brief Compute the product of a row vector with a matrix
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs A row vector
     * @param [in] rhs A matrix
     * @return The rwo vector result of the product between @p lhs and @p rhs
     */
    template<typename T, size_t N>
    inline vec<T, N> const operator*(vec<T, N> const& lhs, mtx<T, N> const& rhs)
    {
        vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = dot(lhs, rhs.col(i).as_vec());
        }
        return result;
    }

    /**
     * @brief Compute the product of a matrix with a scalar
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs A scalar
     * @param [in] rhs A matrix
     * @return The matrix @p rhs scaled by @p lhs
     */
    template<typename T, size_t N>
    inline mtx<T, N> const operator*(T const lhs, mtx<T, N> const& rhs)
    {
        return mtx<T, N>(rhs) *= lhs;
    }

    /**
     * @brief Compute the product of a matrix with a scalar
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs A matrix
     * @param [in] rhs A scalar
     * @return The matrix @p lhs scaled by @p rhs
     */
    template<typename T, size_t N>
    inline mtx<T, N> const operator*(mtx<T, N> const& lhs, T const rhs)
    {
        return rhs * lhs;
    }

    /**
     * @brief Compute the determinant of a 2x2 matrix
     * @tparam T Number type (eg float)
     * @param [in] matrix
     * @return The determinant of @p matrix
     */
    template<typename T>
    inline T const determinant(mtx2<T> const& matrix)
    {
        T const a = matrix[0][0]; T const b = matrix[0][1];
        T const c = matrix[1][0]; T const d = matrix[1][1];
        return a * d - c * b;
    }

    /**
     * @brief Compute the determinant of a 3x3 matrix
     * @tparam T Number type (eg float)
     * @param [in] matrix
     * @return The determinant of @p matrix
     */
    template<typename T>
    inline T const determinant(mtx3<T> const& matrix)
    {
        T const a = matrix[0][0]; T const b = matrix[0][1]; T const c = matrix[0][2];
        T const d = matrix[1][0]; T const e = matrix[1][1]; T const f = matrix[1][2];
        T const g = matrix[2][0]; T const h = matrix[2][1]; T const i = matrix[2][2];

        // compute top row diagonals (walking down and to the right from the first row)
        T const a_diag = a * e * i;
        T const b_diag = b * f * g;
        T const c_diag = c * d * h;
        // compute bottomw row diagonals (walking up and to the right from the second row)
        T const g_diag = g * e * c;
        T const h_diag = h * f * a;
        T const i_diag = i * d * b;
        return a_diag + b_diag + c_diag - g_diag - h_diag - i_diag;
    }

    /**
     * @brief Compute the inverse of a 2x2 matrix
     * @tparam T Number type (eg float)
     * @param [in] matrix 
     * @return The inverse of @p matrix
     */
    template<typename T>
    inline mtx2<T> const inverse(mtx2<T> const& matrix)
    {
        T const a = matrix[0][0]; T const b = matrix[0][1];
        T const c = matrix[1][0]; T const d = matrix[1][1];
        T const scalar = constants<T>::one / determinant(matrix);
        return mtx2<T>(scalar * vec4<T>(d, -c, -b, a));
    }

    /**
     * @brief Compute the inverse of a 3x3 matrix
     * @tparam T Number type (eg float)
     * @param [in] matrix
     * @return The inverse of @p matrix
     */
    template<typename T>
    inline mtx3<T> const inverse(mtx3<T> const& matrix)
    {
        mtx3<T> adjunct = mtx3<T>();
        // TODO (stouff) compute adjunct

        T const scalar = constants<T>::one / determinant(matrix);
        return scalar * adjunct;
    }

    /**
     * @brief Construct a matrix that scales in x, y, and z
     * @tparam T Number type (eg float)
     * @param [in] scalars The scalars for scaling in x, y, and z
     * @return The scale matrix
     */
    template<typename T> inline mtx4<T> scale(vec<T, 3> const& scalars) { return mtx4<T>::scale(scalars); }

    /**
     * @brief Construct a matrix that scales in x
     * @tparam T Number type (eg float)
     * @param [in] scalar 
     * @return The scale matrix
     */
    template<typename T> inline mtx4<T> scale_x(T const scalar) { return mtx4<T>::scale(vec<T, 3>(scalar, T(1), T(1))); }

    /**
     * @brief Construct a matrix that scales in y
     * @tparam T Number type (eg float)
     * @param [in] scalar
     * @return The scale matrix
     */
    template<typename T> inline mtx4<T> scale_y(T const scalar) { return mtx4<T>::scale(vec<T, 3>(T(1), scalar, T(1))); }

    /**
     * @brief Construct a matrix that scales in z
     * @tparam T Number type (eg float)
     * @param [in] scalar
     * @return The scale matrix
     */
    template<typename T> inline mtx4<T> scale_z(T const scalar) { return mtx4<T>::scale(vec<T, 3>(T(1), T(1)), scalar); }

    /**
     * @brief Construct a matrix that translates in x, y, and z
     * @tparam T Number type (eg float)
     * @param [in] scalars The scalars for translating in x, y, and z
     * @return The translation matrix
     */
    template<typename T> inline mtx4<T> translate(vec<T, 3> const& scalars) { return mtx4<T>::translate(scalars); }

    /**
     * @brief Construct a matrix that translates in x
     * @tparam T Number type (eg float)
     * @param [in] scalar
     * @return The translation matrix
     */
    template<typename T> inline mtx4<T> translate_x(T const scalar) { return mtx4<T>::translate(vec<T, 3>(scalar, T(0), T(0))); }

    /**
     * @brief Construct a matrix that translates in y
     * @tparam T Number type (eg float)
     * @param [in] scalar
     * @return The translation matrix
     */
    template<typename T> inline mtx4<T> translate_y(T const scalar) { return mtx4<T>::translate(vec<T, 3>(T(0), scalar, T(0))); }

    /**
     * @brief Construct a matrix that translates in z
     * @tparam T Number type (eg float)
     * @param [in] scalar
     * @return The translation matrix
     */
    template<typename T> inline mtx4<T> translate_z(T const scalar) { return mtx4<T>::translate(vec<T, 3>(T(0), T(0)), scalar); }

    /**
     * @brief Construct a matrix that rotates about the x-axis
     * @tparam T Number type (eg float)
     * @param [in] theta 
     * @return The rotation matrix
     */
    template<typename T>
    inline mtx4<T> rotate_x(T const theta)
    {
        mtx4<T> result;
        result.row(1) = vec<T, 4>(T(0), std::cos(theta), -std::sin(theta), T(0));
        result.row(2) = vec<T, 4>(T(0), std::sin(theta),  std::cos(theta), T(0));
        return result;
    }

    /**
     * @brief Construct a matrix that rotates about the y-axis
     * @tparam T Number type (eg float)
     * @param [in] theta
     * @return The rotation matrix
     */
    template<typename T>
    inline mtx4<T> rotate_y(T const theta)
    {
        mtx4<T> result;
        result.row(0) = vec<T, 4>( std::cos(theta), T(0), std::sin(theta), T(0));
        result.row(2) = vec<T, 4>(-std::sin(theta), T(0), std::cos(theta), T(0));
        return result;
    }

    /**
     * @brief Construct a matrix that rotates about the z-axis
     * @tparam T Number type (eg float)
     * @param [in] theta
     * @return The rotation matrix
     */
    template<typename T>
    inline mtx4<T> rotate_z(T const theta)
    {
        mtx4<T> result;
        result.row(0) = vec<T, 4>(std::cos(theta), -std::sin(theta), T(0), T(0));
        result.row(1) = vec<T, 4>(std::sin(theta),  std::cos(theta), T(0), T(0));
        return result;
    }

    /**
     * @brief Compute a rotation matrix from euler angles about x -> y -> z
     * @tparam T Number Type (eg float)
     * @param [in] x 
     * @param [in] y 
     * @param [in] z 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_xyz(T const x, T const y, T const z) { return (rotate_x(x) *= rotate_y(y)) *= rotate_z(z); }

    /**
     * @brief Compute a rotation matrix from euler angles about x -> z -> y
     * @tparam T Number Type (eg float)
     * @param [in] x 
     * @param [in] z 
     * @param [in] y 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_xzy(T const x, T const z, T const y) { return (rotate_x(x) *= rotate_z(z)) *= rotate_y(y); }

    /**
     * @brief Compute a rotation matrix from euler angles about y -> x -> z
     * @tparam T Number Type (eg float)
     * @param [in] y 
     * @param [in] x 
     * @param [in] z 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_yxz(T const y, T const x, T const z) { return (rotate_y(y) *= rotate_x(x)) *= rotate_z(z); }

    /**
     * @brief Compute a rotation matrix from euler angles about y -> z -> x
     * @tparam T Number Type (eg float)
     * @param [in] y 
     * @param [in] z 
     * @param [in] x 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_yzx(T const y, T const z, T const x) { return (rotate_y(y) *= rotate_z(z)) *= rotate_x(x); }

    /**
     * @brief Compute a rotation matrix from euler angles about z -> x -> y
     * @tparam T Number Type (eg float)
     * @param [in] z 
     * @param [in] x 
     * @param [in] y 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_zxy(T const z, T const x, T const y) { return (rotate_z(z) *= rotate_x(x)) *= rotate_y(y); }

    /**
     * @brief Compute a rotation matrix from euler angles about z -> y -> x
     * @tparam T Number Type (eg float)
     * @param [in] z 
     * @param [in] y 
     * @param [in] x 
     * @return The rotation matrix
     */
    template<typename T> inline mtx4<T> rotate_zyx(T const z, T const y, T const x) { return (rotate_z(z) *= rotate_y(y)) *= rotate_x(x); }

    /**
     * @brief Construct a matrix that rotates the plane
     * @tparam T Number type (eg float)
     * @param [in] theta
     * @return The rotation matrix
     */
    template<typename T>
    inline mtx<T, 2> rotate(T const theta)
    {
        mtx<T, 2> result;
        result.row(0) = vec<T, 2>(std::cos(theta), -std::sin(theta));
        result.row(1) = vec<T, 2>(std::sin(theta),  std::cos(theta));
        return result;
    }

    /**
     * @brief Construct a view matrix
     * @tparam T Number type (eg float)
     * @param [in] eye The camera eye
     * @param [in] look The look direction
     * @param [in] right The right direction
     * @param [in] up The up direction
     * @return The view matrix
     */
    template<typename T>
    inline mtx4<T> view(vec3<T> const& eye, vec3<T> const& look, vec3<T> const& right, vec3<T> const& up)
    {
        vec3<T> v = -look;
        vec3<T> r = right;
        vec3<T> u = up;

        mtx4<T> transform;
        transform[0] = vec4<T>(r, -dot(r, eye));
        transform[1] = vec4<T>(u, -dot(u, eye));
        transform[2] = vec4<T>(v, -dot(v, eye));
        transform[3] = vec4<T>(vec3<T>(), constants<T>::one);
        return transform;
    }

    /**
     * @brief Construct a matrix that computes an orthographic projection
     * @tparam T Number type (eg float)
     * @param [in] l Left plane
     * @param [in] r Right plane
     * @param [in] b Bottom plane
     * @param [in] t Top plane
     * @param [in] n Near plane
     * @param [in] f Far plane
     * @return The projection matrix
     */
    template<typename T>
    inline mtx4<T> orthographic(T const l, T const r, T const b, T const t, T const n, T const f)
    {
        T constexpr two = constants<T>::two;
        vec<T, 3> scalars(two / (r - l), two / (t - b), -two / (f - n));
        vec<T, 3> translators(-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n));
        return mtx4<T>::scale(scalars) * mtx4<T>::translate(translators);
    }

    /**
     * @brief Construct a matrix that computes a perspective projection
     * @tparam T Number type (eg float)
     * @param [in] fov_y Field of view in the y axis
     * @param [in] aspect Aspect ratio (width/height = x/y)
     * @param [in] near_plane Near plane
     * @param [in] far_plane Far plane
     * @return The projection matrix
     */
    template<typename T>
    inline mtx4<T> perspective(T const fov_y, T const aspect, T const near_plane, T const far_plane)
    {
        T y_scale = T(1.0) / std::tan(T(0.5) * fov_y);
        T x_scale = y_scale / aspect;
        mtx4<T> result;
        result[0][0] = x_scale;
        result[1][1] = y_scale;
        result[2][2] = far_plane / (near_plane - far_plane);
        result[2][3] = near_plane * far_plane / (near_plane - far_plane);
        result[3][2] = -1;
        return result;
    }

    /**
     * @brief Compute a matrix that rotates 3-space around @p axis by @p theta
     * @tparam T Number type (eg float)
     * @param [in] axis Unit vector defining the axis of rotation
     * @param [in] theta 
     * @note @p axis must be a unit vector
     * @return The rotation matrix
     */
    template<typename T>
    inline mtx4<T> rotate(vec<T, 3> const& axis, T const theta)
    {
        // perform computations once
        T const cosine = std::cos(theta);
        T const sine   = std::sin(theta);
        T const comp   = T(1) - cosine;     // complement of the cosine

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

    /**
     * @brief Compute a matrix that orbits 3-space around @p focus by @p delta_phi and @p delta_theta
     * @tparam T Number type (eg float)
     * @param [in] focus Center point of the orbit
     * @param [in] right Direction defining what direction is to the right
     * @param [in] delta_phi
     * @param [in] delta_theta 
     * @note Angles @p delta_phi and @p delta_theta are spherical coordinates measured with @p focus as the origin
     * @note @p right must be a unit vector
     * @return The transformation matrix
     */
    template<typename T>
    inline mtx4<T> orbit(vec<T, 3> const& focus, vec<T, 3> const& right, T const delta_phi, T const delta_theta)
    {
        mtx4<T> translate = mtx4<T>::translate(-focus);
        mtx4<T> pitch = rotate(right, delta_phi);
        mtx4<T> yaw = rotate(vec<T, 3>(0, 0, 1), delta_theta);
        mtx4<T> invert_translation = mtx4<T>::translate(focus);
        return invert_translation * yaw * pitch * translate;
    }

    /**
     * @brief Write the matrix @p rhs to the std::ostream @p s
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in,out] s
     * @param [in] rhs
     * @return A reference to @p s
     */
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