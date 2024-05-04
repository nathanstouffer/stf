#pragma once

#include <vector>

#include "stf/enums.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T>
    class polygon final
    {
    public:

        using vec_t = math::vec2<T>;
        using aabb_t = geom::aabb2<T>;

    public:

        polygon() : polygon(std::vector<vec_t>()) {}
        polygon(std::vector<vec_t> const& points) : m_points(points), m_aabb(aabb_t::fit(points)) {}

        inline bool is_empty() const { return m_points.size() < 3; }
        inline size_t size() const { return is_empty() ? 0 : m_points.size(); } 

        inline segment2<T> edge(size_t i) const { return segment2<T>(m_points[i], m_points[(i + 1) % m_points.size()]); }

        inline void clear() { m_points.clear(); m_aabb = aabb_t::nothing(); }
        inline void reserve(size_t const size) { m_points.reserve(size); }
        inline void push_back(vec_t const& x) { m_points.push_back(x); m_aabb.fit(x); }

        inline vec_t const& operator[](size_t i) const { return m_points[i]; }

        inline void write(size_t i, vec_t const& x) { m_points[i] = x; m_aabb = aabb_t::fit(m_points); }

        // bool indicates whether the returned boundary should be 'closed' (by adding the first point at the end)
        // or if it should be left open
        geom::polyline2<T> boundary(bool close) const
        {
            geom::polyline2<T> polyline(m_points);
            if (close)
            {
                polyline.push_back(m_points.front());
            }
            return polyline;
        }

        bool is_convex() const
        {
            // early out for malformed polygons
            if (m_points.size() < 3) { return false; }

            size_t clockwise = 0;
            size_t anticlockwise = 0;

            size_t size = m_points.size();
            for (size_t i = 0; i < size; ++i)
            {
                // grab three consecutive points
                vec_t const& a = m_points[(i + 0) % size];
                vec_t const& b = m_points[(i + 1) % size];
                vec_t const& c = m_points[(i + 2) % size];
                T orientation = math::orientation(a, b, c);
             
                // update counts
                if (orientation > math::constants<T>::zero) { ++anticlockwise; }
                if (orientation < math::constants<T>::zero) { ++clockwise; }
                
                // if we have different orientations, then the polygon is not convex
                if (clockwise && anticlockwise) { return false; }
            }
            return true;        // fallthrough to return true
        }

        // TODO write this function
        // bool is_simple() const;

        // computed using the trapezoid formula for polygon area on https://en.wikipedia.org/wiki/Shoelace_formula
        T signed_area() const
        {
            T sum = math::constants<T>::zero;

            // early out for malformed polygons
            if (m_points.size() < 3) { return sum; }

            // iterate over all segments
            for (size_t i = 0; i < m_points.size(); ++i)
            {
                geom::segment2<T> seg = edge(i);
                sum += (seg.a.y + seg.b.y) * (seg.a.x - seg.b.x);
            }

            return math::constants<T>::half * sum;
        }

        inline T area() const { std::abs(signed_area()); }

        T contains(vec_t const& p, stf::boundary const type) const
        {
            // we shoot a ray out from point in +x and count the number of edges that are crossed
            // crossing_count is odd  => point is in polygon
            // crossing_count is even => point is not in polygon
            size_t crossing_count = 0;

            // early out for malformed polygons
            if (m_points.size() < 3) { return false; }

            // iterate over all edges, computing if the ray crosses the edge
            for (size_t i = 0; i < m_points.size(); ++i)
            {
                geom::segment2<T> seg = edge(i);
                if (seg.distance_to(p) == math::constants<T>::zero)     // early out if the point is on the boundary
                {
                    return (type == stf::boundary::CLOSED) ? true : false;
                }
                else if (seg.a.y == seg.b.y && p.y == seg.a.y)           // case where the segment is horizontal with the same y value as p.y
                {
                    // we also know the point to not be on the boundary because of the of the first condition
                    if (p.x < seg.a.x) { ++crossing_count; }
                }
                else if (seg.range(1).contains(p.y) && p.y != seg.b.y)  // consider the general case where we have a sloped, half-open segment
                {
                    if (seg.a.x == seg.b.x)     // check for a vertical line
                    {
                        if (p.x < seg.a.x) { ++crossing_count; }
                    }
                    else
                    {
                        // we compute the x coordinate of the pair (x, p.y) that is on the line defined by seg
                        // if the ray begins before that coordinate, then the ray crosses this segment
                        T const slope_inv = math::constants<T>::one / seg.slope();
                        T const x = slope_inv * (p.y - seg.a.y) + seg.a.x;
                        if (p.x < x) { ++crossing_count; }
                    }
                }
            }

            // crossing_count is odd  => point is in polygon
            // crossing_count is even => point is not in polygon
            return crossing_count % 2 == 1;
        }

        T signed_distance_to(vec_t const& point) const
        {
            T dist = math::constants<T>::pos_inf;
            for (size_t i = 0; i < m_points.size(); ++i)
            {
                dist = std::min(dist, edge(i).distance_to(point));
            }
            return (contains(point)) ? -dist : dist;
        }

        inline T distance_to(vec_t const& point) const { return std::abs(signed_distance_to(point)); }

        polygon& translate(vec_t const& delta)
        {
            for (vec_t& point : m_points)
            {
                point += delta;
            }
            m_aabb.translate(delta);
            return *this;
        }

        polygon translated(vec_t const& delta) const { return polygon(*this).translate(delta); }

        polygon& scale(T const scalar)
        {
            for (vec_t& point : m_points)
            {
                point *= scalar;
            }
            m_aabb.scale(scalar);
            return *this;
        }

        polygon scaled(T const scalar) const { return polygon(*this).scale(scalar); }

        inline aabb_t const& aabb() const { return m_aabb; }
        inline std::vector<vec_t> const& points() const { return m_aabb; }

        inline size_t byte_count() const { return vec_t::byte_count() * m_points.capacity() + aabb_t::byte_count(); }

    private:

        std::vector<vec_t> m_points;
        aabb_t m_aabb;

    };

} // stf::geom