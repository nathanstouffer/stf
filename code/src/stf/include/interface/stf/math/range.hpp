#pragma once

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"

namespace stf::math
{

    template<typename T>
    struct range final
    {

        T a;
        T b;

        range() : a(constants<T>::zero), b(constants<T>::zero) {}
        range(T const _a, T const _b) : a(_a), b(_b) {}

        inline bool is_empty(boundary type)
        {
            switch (type)
            {
                case boundary::CLOSED: return a > b; break;
                case boundary::OPEN: return a >= b; break;
                default: return false;
            }
        }

        inline bool contains(T const x, boundary const type) const { return contains(a, b, x, type); }
        inline bool contains(range const& rhs) const { return a <= rhs.a && rhs.b <= b; }
        inline bool intersects(range const& rhs) const { return !(rhs.b < a || b < rhs.a); }

        static inline bool contains(T const a, T const b, T const x, boundary const type)
        {
            switch (type)
            {
                case boundary::CLOSED: return a <= x && x <= b; break;
                case boundary::OPEN: return a < x && x < b; break;
                default: return false;
            };
        }

    };

} // stf::math