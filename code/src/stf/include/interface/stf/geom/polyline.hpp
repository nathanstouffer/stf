#pragma once

#include <vector>

#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T, size_t N>
    class polyline final
    {
    public:

        using vec_t = math::vec<T, N>;
        using aabb_t = geom::aabb<T, N>;

    public:

        polyline() : polyline(std::vector<vec_t>()) {}
        polyline(std::vector<vec_t> const& points) : m_points(points), m_aabb(aabb_t::fit(points)) {}

        inline bool is_empty() const { return m_points.size() < 2; }
        inline size_t size() const { return is_empty() ? 0 : m_points.size(); } 

        inline segment<T, N> edge(size_t i) const { return segment<T, N>(m_points[i], m_points[i + 1]); }

        inline void clear() { m_points.clear(); m_aabb = aabb_t::nothing(); }
        inline void reserve(size_t const size) { m_points.reserve(size); }
        inline void push_back(vec_t const& x) { m_points.push_back(x); m_aabb.fit(x); }

        inline vec_t const& operator[](size_t i) const { return m_points[i]; }

        inline void write(size_t i, vec_t const& x) { m_points[i] = x; m_aabb = aabb_t::fit(m_points); }

        inline T length() const
        {
            T len = math::constants<T>::zero;
            if (m_points.size() >= 2)
            {
                for (size_t i = 0; i + 1 < m_points.size(); ++i)
                {
                    len += (m_points[i + 1] - m_points[i]).length();
                }
            }
            return len;
        }

        T distance_to(vec_t const& x) const
        {
            T dist = math::constants<T>::pos_inf;
            for (size_t i = 0; i + 1 < m_points.size(); ++i)
            {
                dist = std::min(dist, edge(i).distance_to(x));
            }
            return dist;
        }

        vec_t interpolate(T const t) const
        {
            if (t <= math::constants<T>::zero) { return m_points.front(); }
            else if (t < math::constants<T>::one)
            {
                T target = t * length();
                T traveled = math::constants<T>::zero;
                for (size_t i = 0; i + 1 < m_points.size(); ++i)
                {
                    segment<T, N> seg = edge(i);        // edge we are processing
                    traveled += seg.length();           // add the length
                    if (target < traveled)              // if we overshot, then we have found the correct segment
                    {
                        // compute the amount we need to travel backwards from the endpoint of the segment
                        T overshot = traveled - target;
                        vec_t offset = overshot * seg.direction();
                        return seg.b - offset;
                    }
                }

                // made it through the whole polyline, return the last point (though this should never be reached)
                return m_points.back();
            }
            else { return m_points.back(); }
        }

        polyline& translate(vec_t const& delta)
        {
            for (vec_t& point : m_points)
            {
                point += delta;
            }
            m_aabb.translate(delta);
            return *this;
        }

        polyline translated(vec_t const& delta) const { return polyline(*this).translate(delta); }

        polyline& scale(T const scalar)
        {
            for (vec_t& point : m_points)
            {
                point *= scalar;
            }
            m_aabb.scale(scalar);
            return *this;
        }

        polyline scaled(T const scalar) const { return polyline(*this).scale(scalar); }

        inline aabb_t const& aabb() const { return m_aabb; }
        inline std::vector<vec_t> const& points() const { return m_aabb; }

        inline size_t byte_count() const { return vec_t::byte_count() * m_points.capacity() + aabb_t::byte_count(); }

    private:

        std::vector<vec_t> m_points;
        aabb_t m_aabb;

    };

    // delete invalid polyline specialization
    template<typename T> struct polyline<T, 0> { polyline() = delete; };
    template<typename T> struct polyline<T, 1> { polyline() = delete; };

    // type aliases for ease of use
    template<typename T> using polyline2 = polyline<T, 2>;
    template<typename T> using polyline3 = polyline<T, 3>;


} // stf::geom