#pragma once

#include <cstring>

#include <array>
#include <limits>
#include <vector>

#include "stf/geom/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

/**
 * @file obb.hpp
 * @brief A file containing a templated obb class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief An obb class representing oriented boxes in R^n
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     */
    template<typename T, size_t N>
    struct obb final
    {
    public:

        /**
         * @brief Type alias for vector type
         */
        using vec_t = math::vec<T, N>;

        /**
         * @brief Type alias for the basis of the box
         * @note The basis is assumed to be orthonormal
         */
        using basis_t = std::array<vec_t, N>;

    public:

        static basis_t const canonical_basis()
        {
            basis_t basis;
            for (size_t d = 0; d < N; ++d)
            {
                vec_t dir = vec_t(math::constants<T>::zero);
                dir[d] = math::constants<T>::one;
                basis[d] = dir;
            }
            return basis;
        }

        /**
         * @brief Convert a rotation matrix to a basis
         * @param [in] rotation 
         * @return The basis corresponding to @p rotation
         * @note @p rotation is assumed to be orthonormal
         */
        static basis_t const to_basis(math::mtx<T, N> const& rotation)
        {
            basis_t basis;
            for (size_t d = 0; d < N; ++d)
            {
                basis[d] = rotation.col(d);
            }
            return basis;
        }

    public:

        /**
         * @brief Default constructor -- encompasses all of R^n
         */
        obb() : obb(canonical_basis()) {}

        /**
         * @brief Construct from a basis -- encompasses all of R^n
         * @param [in] basis
         */
        explicit obb(basis_t const& basis) : obb(vec_t(math::constants<T>::zero), basis, vec_t(math::constants<T>::neg_inf)) {}

        /**
         * @brief Construct from an @ref aabb
         * @param [in] aabb
         */
        explicit obb(aabb<T, N> const& aabb) : obb(aabb.center(), canonical_basis(), math::constants<T>::half * aabb.diagonal()) {}

        /**
         * @brief Construct from a center, a rotation matrix, and half-extents
         * @param [in] center
         * @param [in] rotation
         * @param [in] half_extents
         * @note @p rotation is assumed to be orthonormal
         */
        obb(vec_t const& center, math::mtx<T, N> const& rotation, vec_t const& half_extents) : obb(center, to_basis(rotation), half_extents) {}

        /**
         * @brief Construct from a center, basis, and half-extents
         * @param [in] center
         * @param [in] basis
         * @param [in] half_extents
         */
        obb(vec_t const& center, basis_t const& basis, vec_t const& half_extents) : m_center(center), m_basis(basis), m_half_extents(half_extents) {}

        /**
         * @brief Compute the @p i vertex of an @ref obb
         * @param [in] i
         * @return The position of the @p i vertex
         */
        vec_t vertex(size_t const i) const
        {
            vec_t position = m_center;
            for (size_t d = 0; d < N; ++d)
            {
                vec_t offset = m_half_extents[d] * m_basis[d];
                position += ((i & (1 << d)) != 0) ? offset : -offset;
            }
            return position;
        }

        /**
         * @brief Compute whether a point is contained in an @ref obb
         * @param [in] point
         * @return Whether or not @p point is contained in @p this
         */
        bool const contains(vec_t const& x) const
        {
            for (size_t d = 0; d < N; ++d)
            {
                vec_t const& basis = m_basis[d];
                T const l = math::dot(point - m_center, basis);
                T& half_extent = m_half_extents[d];
                if (std::abs(l) > half_extent)
                {
                    return false;
                }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute whether one @ref obb contains another
         * @param [in] rhs
         * @return Whether or not @p rhs is contained in @p this
         */
        bool const contains(obb const& rhs) const
        {
            for (size_t v = 0; v < obb::vertex_count(); ++v)
            {
                if (!contains(rhs.vertex(v))) { return false; }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute the projection of an @ref obb onto an axis
         * @param [in] axis
         * @return The interval of projection onto the axis
         * @note @p axis is assumed to be a unit vector
         */
        math::interval<T> projection(vec_t const& axis) const
        {
            math::interval<T> interval(math::constants<T>::pos_inf, math::constants<T>::neg_inf);
            for (size_t v = 0; v < obb::vertex_count(); ++d)
            {
                T const l = math::dot(vertex(i), axis);
                interval.a = std::min(interval.a, l);
                interval.b = std::max(interval.b, l);
            }
            return interval;
        }

        /**
         * @brief Fit a point to an @ref obb in place
         * @param [in] point
         * @return A reference to @p this
         */
        obb& fit(vec_t const& point)
        {
            for (size_t d = 0; d < N; ++d)
            {
                vec_t const& basis = m_basis[d];
                T const l = math::dot(point - m_center, basis);
                T& half_extent = m_half_extents[d];
                if (std::abs(l) > half_extent)
                {
                    vec_t min = (l < -half_extent) ? m_center + l * basis : m_center - half_extent * basis;
                    vec_t max = (l >  half_extent) ? m_center + l * basis : m_center + half_extent * basis;
                    m_center = math::constants<T>::half * (min + max);
                    half_extent = std::abs(math::dot(point - m_center, basis));
                }
            }
            return *this;
        }

        /**
         * @brief Fit an @ref obb
         * @param [in] x
         * @return A fitted copy of @p this
         */
        obb fitted(vec_t const& x) const { return obb(*this).fit(x); }

    public:

        vec_t const& center() const { return m_center; }
        basis_t const& basis() const { return m_basis; }
        vec_t const& half_extents() const { return m_half_extents; }

    public:

        /**
         * @brief Construct an @ref obb that minimally encompasses a set of points
         * @param [in] points
         * @return An @ref obb that minimally encompasses @p points
         */
        static obb const fit(basis_t const& basis, std::vector<vec_t> const& points)
        {
            obb box = obb(basis);
            for (vec_t const& point : points)
            {
                box.fit(point);
            }
            return box;
        }

        inline static size_t const vertex_count() { return 1 << N; }

        /**
         * @brief Compute the number of bytes allocated by @ref obb
         * @return The byte count
         */
        inline static size_t const byte_count() { return (2 + N) * vec_t::byte_count(); }

    private:

        vec_t m_center;
        basis_t m_basis;
        vec_t m_half_extents;

    };

    /// @cond DELETED
    /**
     * @brief Delete invalid obb specialization
     */
    template<typename T> struct obb<T, 0> { obb() = delete; };
    /// @endcond

    /**
     * @brief Type alias for a 2D @ref obb
     * @tparam T Number type (eg float)
     */
    template<typename T> using obb2 = obb<T, 2>;

    /**
     * @brief Type alias for a 3D @ref obb
     * @tparam T Number type (eg float)
     */
    template<typename T> using obb3 = obb<T, 3>;

    /**
     * @brief Compute whether or not an axis separates two @ref obb
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] axis 
     * @param [in] lhs 
     * @param [in] rhs 
     * @return Whether or not @p axis separates @p lhs and @p rhs
     * @note @p axis is assumed to be a unit vector
     */
    template<typename T, size_t N>
    bool const separates(math::vec<T, N> const& axis, obb<T, N> const& lhs, obb<T, N> const& rhs)
    {
        math::interval<T> l = lhs.projection(axis);
        math::interval<T> r = rhs.projection(axis);
        return !l.intersects(r);
    }

    /**
     * @brief Compute whether or not two 2D obbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs 
     * @param [in] rhs 
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    bool const intersect(obb2<T> const& lhs, obb2<T> const& rhs)
    {
        // intersection is computed using the separating axis test. if two 2d obbs do not intersect, then the set of edge
        // normals will contain a separating axis
        for (math::vec2<T> const& axis : lhs.basis())
        {
            if (separates(axis, lhs, rhs))
            {
                return false;
            }
        }
        for (math::vec2<T> const& axis : rhs.basis())
        {
            if (separates(axis, lhs, rhs))
            {
                return false;
            }
        }
        return true;    // fallthrough to true
    }

    /**
     * @brief Compute whether or not two 3D obbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    bool const intersect(obb3<T> const& lhs, obb3<T> const& rhs)
    {
        // intersection is computed using the separating axis test. if two 3d obbs do not intersect, then the union of the
        // following two sets will contain a separating axis
        //      1. the set of face normals
        //      2. the set of cross products of pairs of edges from each obb
        // I do not know why we need to also test the cross products
        for (math::vec3<T> const& axis : lhs.basis())
        {
            if (separates(axis, lhs, rhs))
            {
                return false;
            }
        }
        for (math::vec3<T> const& axis : rhs.basis())
        {
            if (separates(axis, lhs, rhs))
            {
                return false;
            }
        }
        for (math::vec3<T> const& l : lhs.basis())
        {
            for (math::vec3<T> const& r : rhs.basis())
            {
                math::vec3<T> const axis = math::cross(l, r);
                if (axis.length_squared() > math::constants<T>::zero && separates(axis, lhs, rhs))
                {
                    return false;
                }
            }
        }
        return true;    // fallthrough to true
    }

    /**
     * @brief Write the @ref obb @p rhs to the std::ostream @p s
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in,out] s
     * @param [in] rhs
     * @return A reference to @p s
     */
    template <typename T, size_t N>
    inline std::ostream& operator<<(std::ostream& s, obb<T, N> const& rhs)
    {
        s << "{ center: " << rhs.center() << ", extents: " << rhs.extents() << " }";
        return s;
    }

} // stf::geom