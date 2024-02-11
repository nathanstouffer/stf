#pragma once

#include <cstring>

#include <limits>
#include <vector>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T, size_t N>
    struct aabb final
    {
    public:

        using vec_t = math::vec<T, N>;

    public:

        vec_t min;
        vec_t max;

        // defining constructors
        aabb(vec_t const& _min, vec_t const& _max) : min(_min), max(_max) {}
        
        // call-through constructors
        aabb(vec_t const& _min, T const length) : aabb(_min, min + vec_t(length)) {}
        aabb() : aabb(vec_t(math::constants<T>::neg_inf), vec_t(math::constants<T>::pos_inf)) {}

        //    6----7
        //   /|   /|
        //  2----3 |
        //  | 4--|-5
        //  |/   |/
        //  0----1
        // 0 is the min
        // 3 is the max in 2D and 7 is the max in 3D
        vec_t vertex(size_t index) const
        {
            vec_t vert = min;
            for (size_t i = 0; i < N; ++i)
            {
                if ((index & (1 << i)) != 0)
                {
                    vert[i] = max[i];
                }
            }
            return vert;
        }

        inline vec_t const length() const { return max - min; }
        inline vec_t const center() const { return min + (math::constants<T>::half * length()); }

        aabb& scale(T const scalar) { min *= scalar; max *= scalar; return *this; }
        aabb scaled(T const scalar) const { return aabb(*this).scale(scalar); }

        aabb& translate(vec_t const& delta) { min += delta; max += delta; return *this; }
        aabb translated(vec_t const& delta) const { return aabb(*this).translate(delta); }

        aabb& fit(vec_t const& x)
        {
            for (size_t i = 0; i < N; ++i)
            {
                min[i] = std::min(min[i], x[i]);
                max[i] = std::max(max[i], x[i]);
            }
            return *this;
        }

        aabb& fit(aabb const& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                min[i] = std::min(min[i], rhs.min[i]);
                max[i] = std::max(max[i], rhs.max[i]);
            }
            return *this;
        }

        bool contains(vec_t const& x) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool contained = min[i] <= x[i] && x[i] <= max[i];
                if (!contained) { return false; }
            }
            return true;    // fallthrough to true
        }

        bool contains(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool contained = min[i] <= rhs.min[i] && rhs.max[i] <= max[i];
                if (!contained) { return false; }
            }
            return true;    // fallthrough to true
        }

        bool intersects(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool empty = rhs.max[i] < min[i] || max[i] < rhs.min[i];
                if (empty) { return false; }
            }
            return true;    // fallthrough to true
        }

        T volume() const
        {
            T const len = length();
            T measure = math::constants<T>::one;
            for (size_t i = 0; i < N; ++i)
            {
                measure *= (len[i] < math::constants<T>::zero) ? len[i] : math::constants<T>::zero;
            }
            return measure;
        }

    public:

        static aabb everything() { return aabb(); }
        static aabb nothing() { return aabb(vec_t(math::constants<T>::pos_inf), vec_t(math::constants<T>::neg_inf)); }
        static aabb unit() { return aabb(vec_t(math::constants<T>::zero), vec_t(math::constants<T>::one)); }

        static aabb fit(std::vector<vec_t> const& points)
        {
            aabb box = aabb::nothing();
            for (vec_t const& point : points)
            {
                box.fit(point);
            }
            return box;
        }

        inline static size_t byte_count() { return 2 * vec_t::byte_count(); }

    };

    // delete invalid aabb specialization
    template<typename T> struct aabb<T, 0> { aabb() = delete; };

    // type aliases for ease of use
    template<typename T> using aabb2 = aabb<T, 2>;
    template<typename T> using aabb3 = aabb<T, 3>;

    template<typename T, size_t N>
    aabb<T, N> const fit(aabb<T, N> const& lhs, aabb<T, N> const& rhs)
    {
        return aabb<T, N>(lhs).fit(rhs);
    }

    template <typename T, size_t N>
    inline std::ostream& operator<<(std::ostream& s, aabb<T, N> const& rhs)
    {
        s << "{ min: " << rhs.min << ", max: " << rhs.max << " }";
        return s;
    }

} // stf::geom