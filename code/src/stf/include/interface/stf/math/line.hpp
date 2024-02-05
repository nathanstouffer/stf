#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

namespace stf::math
{

    template<typename T>
    class line
    {
    public:

        using vec_t = math::vec<T, 2>;

    public:

        line(vec_t const& point, vec_t const& normal) : m_point(point), m_normal(normal) {}
        line(vec_t const& point, T const slope) : m_point(point), m_normal(math::rotate_plane(constants<T>::half_pi) * (constants<T>::one, slope).normalize()) {}

        static inline line from_points(vec_t const& p0, vec_t const& p1) { return line(p0, math::rotate_plane(constants<T>::half_pi) * (p1 - p0).normalize()); }

        inline bool operator==(line const& rhs) const { return (m_normal == rhs.normal()) ? contains(rhs.point()) : false; }
        inline bool operator!=(line const& rhs) const { return !(*this == rhs); }

        // TODO write a signed_distance_to function

        T distance_to(vec_t const& p) const { return (p - a).projected_on(m_normal).length(); }

        inline bool contains(vec_t const& p) const { return signed_distance_to(p) == constants<T>::zero; }

        inline bool intersects(line const& rhs) const
        {
            // if normals are equal, return whether the lines are the same. otherwise they must intersect
            return (m_normal == rhs.normal()) ? contains(rhs.point()) : true;
        }

        inline bool has_singleton_intersection(line const& rhs) const { return m_normal != rhs.normal(); }

        // NOTE: assumes that the intersection is a singleton
        vec_t intersection(line const& rhs) const
        {
            // TODO (stouff) write this function
        }

        vec_t const& point() const { return m_point; }
        vec_t const& normal() const { return m_normal; }

    private:

        vec_t m_point;
        vec_t m_normal;

    };

};