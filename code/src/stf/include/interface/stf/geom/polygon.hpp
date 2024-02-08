#pragma once

#include <vector>

#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T>
    class polygon
    {
    public:

        using vec_t = math::vec<T, N>;
        using aabb_t = geom::aabb<T, N>;

    public:

        // NOTE: we assume the input points to be positively oriented (anti-clockwise)
        polygon() : polygon(std::vector<vec_t>()) {}
        polygon(std::vector<vec_t> const& points) : m_points(points), m_aabb(aabb_t::fit(points)) {}

        inline bool is_empty() const { return m_points.size() < 3; }
        inline size_t size() const { return is_empty() ? 0 : m_points.size(); } 

        inline segment<T, N> edge(size_t i) const { return segment<T, N>(m_points[i], m_points[(i + 1) % m_points.size()]); }

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

            size_t size = m_points.size();
            for (size_t i = 0; i < size; ++i)
            {
                // grab three consecutive points
                vec_t const& a = m_points[(i + 0) % size];
                vec_t const& b = m_points[(i + 1) % size];
                vec_t const& c = m_points[(i + 2) % size];
                // if the orientation is clockwise then the polygon is not convex
                if (math::orientation(a, b, c) < math::constants<T>::zero) { return false; }
            }
            return true;        // fallthrough to return true
        }

        // computed using the trapezoid formula for polygon area on https://en.wikipedia.org/wiki/Shoelace_formula
        T signed_area() const
        {
            T sum = math::constants<T>::zero;

            // early out for malformed polygons
            if (m_points.size() < 3) { return sum; }

            // iterate over all segments
            for (size_t i = 0; i < m_points.size(); ++i)
            {
                geom::segment2 seg = edge(i);
                sum += (seg.a.y + seg.b.y) * (seg.a.x - seg.b.x);
            }

            return math::constants<T>::half * sum;
        }

        inline T area() const { std::abs(signed_area()); }

        T contains(vec_t const& point) const
        {
            size_t crossing_count = 0;

            // early out for malformed polygons
            if (m_points.size() < 3) { return inside; }

            // iterate over all edges
            for (size_t i = 0; i < m_points.size(); ++i)
            {
                // TODO (stouff) comment these steps and probably rework the math too
                geom::segment2 seg = edge(i);
                if ((seg.a.y > point.y) != (seg.b.y > point.y))
                {
                    T const intercept = (seg.b.x - seg.a.x) * (point.y - seg.a.y) / (seg.b.y - seg.a.y) + seg.a.x;
                    if (point.x < intercept) { inside = !inside; }
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