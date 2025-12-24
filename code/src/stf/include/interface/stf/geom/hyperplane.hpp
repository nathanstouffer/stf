#ifndef STF_GEOM_HYPERPLANE_HPP_HEADER_GUARD
#define STF_GEOM_HYPERPLANE_HPP_HEADER_GUARD

#include "stf/geom/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/transform.hpp"
#include "stf/math/vector.hpp"

/**
 * @file hyperplane.hpp
 * @brief A file containing a templated hyperplane class along with associated functions
 */

namespace stf::geom
{

/**
 * @brief A class to represent a R^{n-1} subspace of R^n
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 */
template <typename T, size_t N>
class hyperplane final
{
public:
    /**
     * @brief Type alias for vector type
     */
    using vec_t = math::vec<T, N>;

public:
    /**
     * @brief Default constructor for a hyperplane
     */
    hyperplane() : hyperplane(vec_t(0), vec_t(math::vec<T, N - 1>(0), 1)) {}

    /**
     * @brief Construct from a point and normal vector
     * @param [in] point
     * @param [in] normal
     */
    hyperplane(vec_t const& point, vec_t const& normal) : m_point(point), m_normal(normal.normalized()) {}

    /**
     * @brief Compute the signed distance from a hyperplane to a point
     * @param [in] p
     * @return The signed distance from @p this to @p p
     */
    T signed_dist(vec_t const& p) const { return math::dot(m_normal, p - m_point); }

    /**
     * @brief Compute the distance from a hyperplane to a point
     * @param [in] p
     * @return The distance from @p this to @p p
     */
    inline T dist(vec_t const& p) const { return std::abs(signed_dist(p)); }

    /**
     * @brief Compute whether a point is contained in R^{n-1} subspace that is the hyperplane
     * @param [in] p
     * @return Whether or not @p this contains @p p
     */
    inline bool contains(vec_t const& p) const { return signed_dist(p) == math::constants<T>::zero; }

    /**
     * @brief Compute the side of the hyperplane that a point lies on
     *   * + => side that the normal points to
     *   * 0 => contained in the hyperplane
     *   * - => side that the anti-normal points to
     * @param [in] p
     * @return The side of @p this that @p p lies on
     */
    inline T side(vec_t const& p) const { return signed_dist(p); }

    /**
     * @brief Compute whether a @ref hyperplane divides an aabb
     * @param [in] aabb
     * @return Whether or not @p this divides @p aabb
     */
    bool divides(geom::aabb<T, N> const& aabb) const
    {
        // compute the extremities in each direction
        vec_t extremity = aabb.extremity(m_normal);
        vec_t anti_extremity = aabb.extremity(-m_normal);
        // compute whether the extremities are on opposite sides of the hyperplane
        return side(extremity) * side(anti_extremity) <= math::constants<T>::zero;
    }

    /**
     * @brief Getter for a point on the plane
     * @return A const reference to a point on the plane
     */
    vec_t const& point() const { return m_point; }

    /**
     * @brief Getter for the normal vector of the plane
     * @return A const reference to the normal vector
     */
    vec_t const& normal() const { return m_normal; }

private:
    vec_t m_point;
    vec_t m_normal;
};

/// @cond DELETED
/**
 * @brief Delete invalid @ref hyperplane specialization
 */
template <typename T>
struct hyperplane<T, 0>
{
    hyperplane() = delete;
};
/// @endcond

/**
 * @brief Type alias for a 2D @ref hyperplane
 * @tparam T Number type (eg float)
 */
template <typename T>
using line = hyperplane<T, 2>;

/**
 * @brief Type alias for a 3D @ref hyperplane
 * @tparam T Number type (eg float)
 */
template <typename T>
using plane = hyperplane<T, 3>;

/**
 * @brief Compute the distance between a hyperplane and a vector
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] plane
 * @param [in] point
 * @return The distance between @p plane and @p point
 */
template <typename T, size_t N>
inline T dist(hyperplane<T, N> const& plane, math::vec<T, N> const& point)
{
    return plane.dist(point);
}

/**
 * @brief Compute the distance between a vector and a hyperplane
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] plane
 * @param [in] point
 * @return The distance between @p point and @p plane
 */
template <typename T, size_t N>
inline T dist(math::vec<T, N> const& point, hyperplane<T, N> const& plane)
{
    return dist(plane, point);
}

/**
 * @brief Compute the signed distance between a hyperplane and a vector
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] plane
 * @param [in] point
 * @return The distance between @p ring and @p point
 */
template <typename T, size_t N>
inline T signed_dist(hyperplane<T, N> const& plane, math::vec<T, N> const& point)
{
    return plane.signed_dist(point);
}

/**
 * @brief Compute the signed distance between a vector and a hyperplane
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] plane
 * @param [in] point
 * @return The distance between @p point and @p plane
 */
template <typename T, size_t N>
inline T signed_dist(math::vec<T, N> const& point, hyperplane<T, N> const& plane)
{
    return signed_dist(plane, point);
}

/**
 * @brief Construct a line passing through two points
 * @tparam T Number type (eg float)
 * @param [in] p
 * @param [in] q
 * @note @p p is used as the point defining the line
 * @return
 */
template <typename T>
line<T> fit_line(math::vec2<T> const& p, math::vec2<T> const& q)
{
    math::vec2<T> const& point = p;
    math::vec2<T> normal = math::rotate((p - q).normalize(), math::constants<T>::half_pi);
    return line<T>(point, normal);
}

/**
 * @brief Construct a plane passing through three points
 * @tparam T Number type (eg float)
 * @param [in] p
 * @param [in] q
 * @param [in] r
 * @note @p p is used as the point defining the point
 * @return
 */
template <typename T>
plane<T> fit_plane(math::vec3<T> const& p, math::vec3<T> const& q, math::vec3<T> const& r)
{
    math::vec3<T> const& point = p;
    math::vec3<T> normal = math::cross(q - p, r - p);
    return plane<T>(point, normal);
}

} // namespace stf::geom
#endif
