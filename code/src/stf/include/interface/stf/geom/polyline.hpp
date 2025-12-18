#pragma once

#include <vector>

#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/vector.hpp"

/**
 * @file polyline.hpp
 * @brief A file containing a templated polyline class along with associated functions
 */

namespace stf::geom
{

/**
 * @brief A class to represent a polyline -- a connected sequence of straight line segments in R^n
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 */
template <typename T, size_t N>
class polyline final
{
  public:
    /**
     * @brief Type alias for vector
     */
    using vec_t = math::vec<T, N>;

    /**
     * @brief Type alias for aabb
     */
    using aabb_t = geom::aabb<T, N>;

    /**
     * @brief Type alias for a line segment
     */
    using seg_t = geom::segment<T, N>;

  public:
    /**
     * @brief Default constructor -- an empty polyline
     */
    polyline() : polyline(std::vector<vec_t>()) {}

    /**
     * @brief Construct from an array of vertices -- segments are formed by adjacent vertices
     * @param [in] vertices
     */
    polyline(std::vector<vec_t> const& vertices)
        : m_vertices(vertices)
        , m_aabb(aabb_t::fit(vertices))
    {
    }

    /**
     * @brief Report whether or not a @ref polyline is empty
     * @note Must have at least two vertices to be non-empty
     * @return Whether or not @p this is empty
     */
    inline bool is_empty() const { return m_vertices.size() < 2; }

    /**
     * @brief Compute the size of the @ref polyline
     * @return The number of vertices in the @ref polyline
     */
    inline size_t size() const { return is_empty() ? 0 : m_vertices.size(); }

    /**
     * @brief Compute whether or not two polylines are equal
     * @param [in] rhs
     * @return Whethor not @p this equals @p rhs
     */
    inline bool operator==(polyline const& rhs) const { return m_vertices == rhs.m_vertices; }

    /**
     * @brief Access an edge of a @ref polyline
     * @param [in] i The index of the edge to return
     * @return The edge at @p i
     */
    inline seg_t edge(size_t const i) const { return seg_t(m_vertices[i], m_vertices[i + 1]); }

    /**
     * @brief Clear the data stored in a @ref polyline
     */
    inline void clear()
    {
        m_vertices.clear();
        m_aabb = aabb_t::nothing();
    }

    /**
     * @brief Reserve memory for a @ref polyline with @p size vertices
     * @param [in] size
     */
    inline void reserve(size_t const size) { m_vertices.reserve(size); }

    /**
     * @brief Add a vertex to the end of a @ref polyline
     * @param [in] vertex
     */
    inline void push_back(vec_t const& vertex)
    {
        m_vertices.push_back(vertex);
        m_aabb.fit(vertex);
    }

    /**
     * @brief Const access to the first vertex of a @ref polyline
     * @return A const reference to the first vertex
     */
    inline vec_t const& front() const { return m_vertices.front(); }

    /**
     * @brief Const access to the last vertex of a @ref polyline
     * @return A const reference to the last vertex
     */
    inline vec_t const& back() const { return m_vertices.back(); }

    /**
     * @brief Const access to a vertex of a @ref polyline
     * @param [in] i
     * @return A const reference to the @p ith vertex
     */
    inline vec_t const& operator[](size_t i) const { return m_vertices[i]; }

    /**
     * @brief Overwrite an existing vertex of a @ref polyline
     * @note This requires re-computing the bounding box
     * @param [in] i The index of the vertex
     * @param [in] vertex The new value of the vertex
     */
    inline void write(size_t const i, vec_t const& vertex)
    {
        m_vertices[i] = vertex;
        m_aabb = aabb_t::fit(m_vertices);
    }

    /**
     * @brief Compute the length of a @ref polyline
     * @return The length of @p this
     */
    inline T length() const
    {
        T len = math::constants<T>::zero;
        if (m_vertices.size() >= 2)
        {
            for (size_t i = 0; i + 1 < m_vertices.size(); ++i)
            {
                len += (m_vertices[i + 1] - m_vertices[i]).length();
            }
        }
        return len;
    }

    /**
     * @brief Compute the distance from a @ref polyline to a point
     * @param [in] point
     * @return The distance from @p this to @p point
     */
    T dist_squared(vec_t const& point) const
    {
        T d = math::constants<T>::pos_inf;
        for (size_t i = 0; i + 1 < m_vertices.size(); ++i)
        {
            d = std::min(d, edge(i).dist_squared(point));
        }
        return d;
    }

    /**
     * @brief Compute the distance between a polyline and a vector
     * @param [in] point
     * @return The distance between @p this and @p point
     */
    inline T dist(vec_t const& point) const { return std::sqrt(dist_squared(point)); }

    /**
     * @brief Interpolate along a @ref polyline
     * @p t = 0 is the first vertex and @p t = 1 is the final vertex
     * @param [in] t Time along the @ref polyline
     * @return The interpolated point
     */
    vec_t interpolate(T const t) const
    {
        if (t <= math::constants<T>::zero)
        {
            return m_vertices.front();
        }
        else if (t < math::constants<T>::one)
        {
            T target = t * length();
            T traveled = math::constants<T>::zero;
            for (size_t i = 0; i + 1 < m_vertices.size(); ++i)
            {
                seg_t seg = edge(i);      // edge we are processing
                traveled += seg.length(); // add the length
                if (target < traveled)    // if we overshot, then we have found the correct segment
                {
                    // compute the amount we need to travel backwards from the endpoint of the
                    // segment
                    T overshot = traveled - target;
                    vec_t offset = overshot * seg.direction();
                    return seg.b - offset;
                }
            }

            // made it through the whole polyline, return the last vertex (though this should never
            // be reached)
            return m_vertices.back();
        }
        else
        {
            return m_vertices.back();
        }
    }

    /**
     * @brief Translate a @ref polyline in place
     * @param [in] delta
     * @return A reference to @p this
     */
    polyline& translate(vec_t const& delta)
    {
        for (vec_t& vertex : m_vertices)
        {
            vertex += delta;
        }
        m_aabb.translate(delta);
        return *this;
    }

    /**
     * @brief Translate a @ref polyline
     * @param [in] delta
     * @return A translated copy of @p this
     */
    polyline translated(vec_t const& delta) const { return polyline(*this).translate(delta); }

    /**
     * @brief Scale a @ref polyline in place
     * @param [in] scalar
     * @return A reference to @p this
     */
    polyline& scale(T const scalar)
    {
        for (vec_t& vertex : m_vertices)
        {
            vertex *= scalar;
        }
        m_aabb.scale(scalar);
        return *this;
    }

    /**
     * @brief Scale a @ref polyline
     * @param [in] scalar
     * @return A scaled copy of @p this
     */
    polyline scaled(T const scalar) const { return polyline(*this).scale(scalar); }

    /**
     * @brief Const access to the bounding box
     * @return Const reference to the bounding box
     */
    inline aabb_t const& aabb() const { return m_aabb; }

    /**
     * @brief Const access to the underlying array of vertices
     * @return Const reference to vertices
     */
    inline std::vector<vec_t> const& vertices() const { return m_vertices; }

    /**
     * @brief Compute the number of bytes allocated by a @ref polyline
     * @return The computed number of bytes
     */
    inline size_t byte_count() const
    {
        return vec_t::byte_count() * m_vertices.capacity() + aabb_t::byte_count();
    }

  private:
    std::vector<vec_t> m_vertices;
    aabb_t m_aabb;
};

/// @cond DELETED
/**
 * @brief Delete invalid polyline specialization
 */
template <typename T>
struct polyline<T, 0>
{
    polyline() = delete;
};
/**
 * @brief Delete invalid polyline specialization
 */
template <typename T>
struct polyline<T, 1>
{
    polyline() = delete;
};
/// @endcond

/**
 * @brief Type alias for a 2D @ref polyline
 * @tparam T Number type (eg float)
 */
template <typename T>
using polyline2 = polyline<T, 2>;

/**
 * @brief Type alias for a 3D @ref polyline
 * @tparam T Number type (eg float)
 */
template <typename T>
using polyline3 = polyline<T, 3>;

/**
 * @brief Compute the square of the distance between a polyline and a vector
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] linestring
 * @param [in] point
 * @return The square of the distance between @p linestring and @p point
 */
template <typename T, size_t N>
inline T dist_squared(polyline<T, N> const& linestring, math::vec<T, N> const& point)
{
    return linestring.dist_squared(point);
}

/**
 * @brief Compute the square of the distance between a vector and a polyline
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] point
 * @param [in] linestring
 * @return The square of the distance between @p point and @p linestring
 */
template <typename T, size_t N>
inline T dist_squared(math::vec<T, N> const& point, polyline<T, N> const& linestring)
{
    return dist_squared(linestring, point);
}

/**
 * @brief Compute the distance between a polyline and a vector
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] linestring
 * @param [in] point
 * @return The distance between @p linestring and @p point
 */
template <typename T, size_t N>
inline T dist(polyline<T, N> const& linestring, math::vec<T, N> const& point)
{
    return linestring.dist(point);
}

/**
 * @brief Compute the distance between a vector and a polyline
 * @tparam T Number type (eg float)
 * @tparam N Dimension
 * @param [in] linestring
 * @param [in] point
 * @return The distance between @p point and @p linestring
 */
template <typename T, size_t N>
inline T dist(math::vec<T, N> const& point, polyline<T, N> const& linestring)
{
    return dist(linestring, point);
}

} // namespace stf::geom