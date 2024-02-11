#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/transform.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T, size_t N>
    class hyperplane final
    {
    public:

        using vec_t = math::vec<T, N>;

    public:

        hyperplane(vec_t const& point, vec_t const& normal) : m_point(point), m_normal(normal.normalized()) {}

        T signed_distance(vec_t const& p) const { return m_normal * (p - m_point); }
        inline distance(vec_t const& p) const { return std::abs(signed_distance(p)); }
        inline bool contains(vec_t const& p) const { return signed_distance(p) == math::constants<T>::zero; }

        // + => side that the normal points to
        // 0 => contained in the hyperplane
        // - => side that the anti-normal points to
        inline T side(vec_t const& p) const { return signed_distance(p); }

    private:

        vec_t m_point;
        vec_t m_normal;

    };

    // delete invalid hyperplane specialization
    template<typename T> struct hyperplane<T, 0> { hyperplane() = delete; };

    // type aliases for ease of use
    template<typename T> using line = hyperplane<T, 2>;
    template<typename T> using plane = hyperplane<T, 3>;

    template<typename T>
    line<T> fit_line(math::vec2<T> const& p, math::vec2<T> const& q)
    {
        vec_t const& point = p;
        vec_t normal = math::rotate((p - q).normalize(), math::constants<T>::half_pi);
        return line<T>(point, normal);
    }

    template<typename T>
    plane<T> fit_plane(math::vec3<T> const& p, math::vec3<T> const& q, math::vec3<T> const& r)
    {
        vec_t const& point = p;
        vec_t normal = math::cross(q - p, r - p);
        return line<T>(point, normal);
    }

} // stf::geom