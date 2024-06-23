#pragma once

#include <vector>

#include "stf/enums.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/math/vector.hpp"

/**
 * @file polygon.hpp
 * @brief A file containing a templated polygon class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief A class to represent a polygon
     * @tparam T Number type (eg float)
     */
    template<typename T>
    class polygon final
    {
    public:

        /**
         * @brief Type alias for a vector
         */
        using vec_t = math::vec2<T>;

        /**
         * @brief Type alias for an aabb
         */
        using aabb_t = geom::aabb2<T>;

    public:

        /**
         * @brief Default constructor -- empty @ref polygon
         */
        polygon() : polygon(std::vector<vec_t>()) {}

        /**
         * @brief Construct from an array of vertices -- there is an implicit edge from the last to the first vertex
         * @param [in] vertices 
         */
        polygon(std::vector<vec_t> const& vertices) : m_vertices(vertices), m_aabb(aabb_t::fit(vertices)) {}

        /**
         * @brief Compute whether or not a @ref polygon is empty
         * @note Must have at least 3 vertices to be considered non-empty
         * @return Whether or not @p this is empty
         */
        inline bool is_empty() const { return m_vertices.size() < 3; }

        /**
         * @brief Compute the size of a @ref polygon
         * @return The size of @p this
         */
        inline size_t size() const { return is_empty() ? 0 : m_vertices.size(); } 

        /**
         * @brief Access an edge of a @ref polygon
         * @param [in] i The index of the edge to return
         * @return The edge at @p i
         */
        inline segment2<T> edge(size_t i) const { return segment2<T>(m_vertices[i], m_vertices[(i + 1) % m_vertices.size()]); }

        /**
         * @brief Clear the data stored in a @ref polygon
         */
        inline void clear() { m_vertices.clear(); m_aabb = aabb_t::nothing(); }

        /**
         * @brief Reserve memory for a @ref polygon with @p size vertices
         * @param [in] size
         */
        inline void reserve(size_t const size) { m_vertices.reserve(size); }

        /**
         * @brief Add a vertex to the end of a @ref polygon
         * @param [in] vertex
         */
        inline void push_back(vec_t const& vertex) { m_vertices.push_back(vertex); m_aabb.fit(vertex); }

        /**
         * @brief Const access to a vertex of a @ref polygon
         * @param [in] i
         * @return A const reference to the @p ith vertex
         */
        inline vec_t const& operator[](size_t i) const { return m_vertices[i]; }

        /**
         * @brief Overwrite an existing vertex of a @ref polygon
         * @note This requires re-computing the bounding box
         * @param [in] i The index of the vertex
         * @param [in] vertex The new value of the vertex
         */
        inline void write(size_t i, vec_t const& vertex) { m_vertices[i] = vertex; m_aabb = aabb_t::fit(m_vertices); }

        /**
         * @brief Compute the boundary of a @ref polygon
         * @param [in] close Indicates whether the returned boundary should be 'closed' (by adding the first point to the end) or if it should be left open
         * @return The boundary of @p this
         */
        geom::polyline2<T> boundary(bool const close) const
        {
            geom::polyline2<T> polyline(m_vertices);
            if (close)
            {
                polyline.push_back(m_vertices.front());
            }
            return polyline;
        }

        /**
         * @brief Compute whether or not a @ref polygon is convex
         * @return Whether or not @p this is convex
         */
        bool is_convex() const
        {
            // early out for malformed polygons
            if (m_vertices.size() < 3) { return false; }

            size_t clockwise = 0;
            size_t counterclockwise = 0;

            size_t size = m_vertices.size();
            for (size_t i = 0; i < size; ++i)
            {
                // grab three consecutive points
                vec_t const& a = m_vertices[(i + 0) % size];
                vec_t const& b = m_vertices[(i + 1) % size];
                vec_t const& c = m_vertices[(i + 2) % size];
                T orientation = math::orientation(a, b, c);
             
                // update counts
                if (orientation > math::constants<T>::zero) { ++counterclockwise; }
                if (orientation < math::constants<T>::zero) { ++clockwise; }
                
                // if we have different orientations, then the polygon is not convex
                if (clockwise && counterclockwise) { return false; }
            }
            return true;        // fallthrough to return true
        }

        // TODO write this function
        // bool is_simple() const;
        
        /**
         * @brief Compute the signed area of a @ref polygon
         * Computed using the trapezoid formula for polygon area on https://en.wikipedia.org/wiki/Shoelace_formula
         * @return The signed area of @p this
         */
        T signed_area() const
        {
            T sum = math::constants<T>::zero;

            // early out for malformed polygons
            if (m_vertices.size() < 3) { return sum; }

            // iterate over all segments
            for (size_t i = 0; i < m_vertices.size(); ++i)
            {
                geom::segment2<T> seg = edge(i);
                sum += (seg.a.y + seg.b.y) * (seg.a.x - seg.b.x);
            }

            return math::constants<T>::half * sum;
        }

        /**
         * @brief Compute the area of a @ref polygon
         * @return The area of @p this
         */
        inline T area() const { return std::abs(signed_area()); }

        /**
         * @brief Compute whether or not a query point is contained in a @ref polygon
         * @param [in] query The query point
         * @param [in] type Whether the boundary is open or closed
         * @return Whether or not @p this contains @p query
         */
        bool contains(vec_t const& query, boundary_types const type) const
        {
            // we shoot a ray out from point in +x and count the number of edges that are crossed
            // crossing_count is odd  => point is in polygon
            // crossing_count is even => point is not in polygon
            size_t crossing_count = 0;

            // early out for malformed polygons and bbox query
            if (m_vertices.size() < 3) { return false; }
            if (!m_aabb.contains(query)) { return false; }

            // iterate over all edges, computing if the ray crosses the edge
            for (size_t i = 0; i < m_vertices.size(); ++i)
            {
                geom::segment2<T> seg = edge(i);
                if (seg.distance_to(query) == math::constants<T>::zero)     // early out if the point is on the boundary
                {
                    return type == boundary_types::CLOSED;
                }
                else if (seg.a.y > query.y != seg.b.y > query.y)            // test if the y-range is relevent
                {
                    math::interval<T> x_range = seg.interval(0);
                    if (query.x < x_range.a) { ++crossing_count; }      // avoid floating point work if we know the segment crosses
                    else if (query.x <= x_range.b)                      // make sure the x-range is relevant
                    {
                        if (seg.a.x == seg.b.x)     // check for a vertical line
                        {
                            if (query.x < seg.a.x) { ++crossing_count; }
                        }
                        else
                        {
                            // we compute the x coordinate of the pair (x, query.y) that is on the line defined by seg
                            // if the ray begins before that coordinate, then the ray crosses this segment
                            T const slope_inv = math::constants<T>::one / seg.slope();
                            T const x = slope_inv * (query.y - seg.a.y) + seg.a.x;
                            if (query.x < x) { ++crossing_count; }
                        }
                    }
                }
            }

            // crossing_count is odd  => point is in polygon
            // crossing_count is even => point is not in polygon
            return crossing_count % 2 == 1;
        }

        /**
         * @brief Compute the signed distance from a query point to the boundary of a @ref polygon
         * @param [in] query 
         * @return The signed distance from @p query to the boundary of @p this
         */
        T signed_distance_to(vec_t const& query) const
        {
            T dist = math::constants<T>::pos_inf;
            for (size_t i = 0; i < m_vertices.size(); ++i)
            {
                dist = std::min(dist, edge(i).distance_to(query));
            }
            if (dist == math::constants<T>::zero) { return dist; }
            return (contains(query, boundary_types::OPEN)) ? -dist : dist;
        }

        /**
         * @brief Compute the distance from a query point to the boundary of a @ref polygon
         * @param [in] query 
         * @return The distance form @p query to the boundary of @p this
         */
        inline T distance_to(vec_t const& query) const { return std::abs(signed_distance_to(query)); }

        /**
         * @brief Translate a @ref polygon in place
         * @param [in] delta
         * @return A reference to @p this
         */
        polygon& translate(vec_t const& delta)
        {
            for (vec_t& point : m_vertices)
            {
                point += delta;
            }
            m_aabb.translate(delta);
            return *this;
        }

        /**
         * @brief Translate a @ref polygon
         * @param [in] delta
         * @return A translated copy of @p this
         */
        polygon translated(vec_t const& delta) const { return polygon(*this).translate(delta); }

        /**
         * @brief Scale a @ref polygon in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        polygon& scale(T const scalar)
        {
            for (vec_t& point : m_vertices)
            {
                point *= scalar;
            }
            m_aabb.scale(scalar);
            return *this;
        }

        /**
         * @brief Scale a @ref polygon
         * @param [in] scalar
         * @return A scaled copy of @p this
         */
        polygon scaled(T const scalar) const { return polygon(*this).scale(scalar); }

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
         * @brief Compute the number of bytes allocated by a @ref polygon
         * @return The computed number of bytes
         */
        inline size_t byte_count() const { return vec_t::byte_count() * m_vertices.capacity() + aabb_t::byte_count(); }

    private:

        std::vector<vec_t> m_vertices;
        aabb_t m_aabb;

    };

} // stf::geom