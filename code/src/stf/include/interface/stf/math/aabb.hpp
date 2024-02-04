#pragma once

#include <cstring>

#include <limits>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf::math
{

    template<typename T, size_t N>
    struct aabb
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
        aabb() : aabb(vec_t(constants<T>::neg_inf), vec_t(constants<T>::pos_inf)) {}

        // TODO (stouff) write a vertex indexing function

        inline vec_t const length() const { return max - min; }
        inline vec_t const center() const { return min + (constants<T>::half * length()); }

        bool intersects(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool empty = rhs.max[i] < min[i] || max[i] < rhs.min[i];
                if (empty) { return false; }
            }

            // fallthrough to true
            return true;
        }

        bool contains(aabb const& rhs) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                bool contained = min[i] <= rhs.min[i] && rhs.max[i] <= max[i];
                if (!contained) { return false; }
            }

            // fallthrough to true
            return true;
        }

        T volume() const
        {
            T const len = length();
            T measure = constants<T>::one;
            for (size_t i = 0; i < N; ++i)
            {
                measure *= (len[i] < constants<T>::zero) ? len[i] : constants<T>::zero;
            }
        }

    public:

        static aabb everything() { return aabb(); }
        static aabb nothing() { return aabb(vec_t(constants<T>::pos_inf), vec_t(constants<T>::neg_inf)); }
        static aabb unit() { return aabb(vec_t(constants<T>::zero), vec_t(constants<T>::one)); }

    };

    // delete invalid aabb specialization
    template<typename T> struct aabb<T, 0> { aabb() = delete; };

    // type aliases for ease of use
    template<typename T> using aabb2 = aabb<T, 2>;
    template<typename T> using aabb3 = aabb<T, 3>;

    // TODO (stouff) move this to a member function?
    template<typename T, size_t N>
    aabb<T, N> const fit(aabb<T, N> const& lhs, aabb<T, N> const& rhs)
    {
        aabb<T, N> fitted = aabb<T, N>::nothing();
        for (size_t i = 0; i < N; ++i)
        {
            fitted.min[i] = std::min(lhs.min[i], rhs.min[i]);
            fitted.max[i] = std::max(lhs.max[i], rhs.max[i]);
        }
        return fitted;
    }

    template <typename T, size_t N>
    inline std::ostream& operator<<(std::ostream& s, aabb<T, N> const& rhs)
    {
        s << "{ min: " << rhs.min << ", max: " << rhs.max << " }";
        return s;
    }

} // stf::math