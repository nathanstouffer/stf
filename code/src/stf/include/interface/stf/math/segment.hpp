#pragma once

#include "stf/math/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/range.hpp"
#include "stf/math/vector.hpp"

namespace stf::math
{

    template<typename T, size_t N>
    struct segment
    {

        using vec_t = math::vec<T, N>;
        using aabb_t = math::aabb<T, N>;

    public:

        vec_t a;
        vec_t b;

        segment() : segment(vec_t(constants<T>::zero), vec_t(constants<T>::zero)) {}
        segment(vec_t const& _a, vec_t const& _b) : a(_a), b(_b) {}

        inline T length() const { return (b - a).length(); }
        inline T slope() const { vec_t diff = delta(); return diff.y / diff.x; }
        inline vec_t delta() const { return b - a; }
        inline vec_t direction() const { return (b - a).normalize(); }

        inline math::range<T> range(size_t i) const { return math::range<T>(a[i], b[i]); }

        inline aabb_t aabb() const
        {
            aabb_t box = aabb_t::nothing();
            box.fit(a);
            box.fit(b);
            return box;
        }

        inline T distance_to(vec_t const& x) const
        {
            vec_t diff = delta();
            T scalar = ((x - a) * diff) / (diff * diff);
            T t = std::max(constants<T>::zero, std::min(constants<T>::one, scalar));
            vec_t proj = a + t * diff;
            return (x - proj).length();
        }

        vec_t interpolate(T const t) const
        {
            if (t <= constants<T>::zero) { return a; }
            else if (t < constants<T>::one) { return (constants<T>::one - t) * a + t * b; }
            else { return b; }
        }

    };

    // delete invalid segment specializations
    template<typename T> struct segment<T, 0> { segment() = delete; };
    template<typename T> struct segment<T, 1> { segment() = delete; };

    // type aliases for ease of use
    template<typename T> using segment2 = segment<T, 2>;
    template<typename T> using segment3 = segment<T, 3>;

} // stf::math