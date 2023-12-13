#pragma once

#include <cstring>

#include <limits>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace math {

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
        aabb() : aabb(vec_t(std::numeric_limits<T>::lowest()), vec_t(std::numeric_limits<T>::max())) {}

        // TODO (stouff) write a vertex indexing function

        inline vec_t const length() const { return max - min; }
        inline vec_t const center() const { return min + (static_cast<T>(0.5) * length()); }

        T volume() const
        {
            T const len = length();
            T measure = T(1);
            for (size_t i = 0; i < N; ++i)
            {
                if (len[i] < T(0))
                {
                    measure *= len[i];
                }
                else
                {
                    measure = T(0);
                }
            }
        }

    public:

        static aabb everything() { return aabb(); }
        static aabb nothing() { return aabb(vec_t(std::numeric_limits<T>::max()), vec_t(std::numeric_limits<T>::lowest())); }
        static aabb unit() { return aabb(vec_t(0), vec_t(1)); }

    };

    // delete invalid aabb specialization
    template<typename T> struct aabb<T, 0> { aabb() = delete; };

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
        return s
    }

} // math
} // stf