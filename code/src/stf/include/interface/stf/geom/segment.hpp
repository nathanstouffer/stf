#pragma once

#include "stf/geom/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/range.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T, size_t N>
    struct segment final
    {

        using vec_t = math::vec<T, N>;
        using aabb_t = geom::aabb<T, N>;

    public:

        vec_t a;
        vec_t b;

        segment() : segment(vec_t(math::constants<T>::zero), vec_t(math::constants<T>::zero)) {}
        segment(vec_t const& _a, vec_t const& _b) : a(_a), b(_b) {}

        inline T length() const { return (b - a).length(); }
        inline T slope() const { vec_t diff = delta(); return diff.y / diff.x; }
        inline vec_t delta() const { return b - a; }
        inline vec_t direction() const { return delta().normalize(); }

        inline math::range<T> range(size_t i) const { return math::range<T>(std::min(a[i], b[i]), std::max(a[i], b[i])); }

        inline aabb_t aabb() const
        {
            aabb_t box = aabb_t::nothing();
            box.fit(a);
            box.fit(b);
            return box;
        }

        inline T distance_to(vec_t const& p) const
        {
            vec_t diff = delta();
            T scalar = ((p - a) * diff) / (diff * diff);
            T t = std::max(math::constants<T>::zero, std::min(math::constants<T>::one, scalar));
            vec_t proj = a + t * diff;
            return (p - proj).length();
        }

        vec_t interpolate(T const t) const
        {
            if (t <= math::constants<T>::zero) { return a; }
            else if (t < math::constants<T>::one) { return (math::constants<T>::one - t) * a + t * b; }
            else { return b; }
        }

    };

    // delete invalid segment specializations
    template<typename T> struct segment<T, 0> { segment() = delete; };
    template<typename T> struct segment<T, 1> { segment() = delete; };

    // type aliases for ease of use
    template<typename T> using segment2 = segment<T, 2>;
    template<typename T> using segment3 = segment<T, 3>;

} // stf::geom