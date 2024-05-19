#pragma once

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"

namespace stf::math
{

    template<typename T>
    struct interval final
    {

        T a;
        T b;

        interval() : a(constants<T>::zero), b(constants<T>::zero) {}
        interval(T const _a, T const _b) : a(_a), b(_b) {}

        inline bool operator==(interval const& rhs) const { return a == rhs.a && b == rhs.b; }

        inline bool is_empty(boundary_types type)
        {
            switch (type)
            {
                case boundary_types::CLOSED: return a > b; break;
                case boundary_types::OPEN: return a >= b; break;
                default: return false;
            }
        }

        inline bool contains(T const x, boundary_types const type) const { return contains(a, b, x, type); }
        inline bool contains(interval const& rhs) const { return a <= rhs.a && rhs.b <= b; }
        inline bool intersects(interval const& rhs) const { return !(rhs.b < a || b < rhs.a); }

        static inline bool contains(T const a, T const b, T const x, boundary_types const type)
        {
            switch (type)
            {
                case boundary_types::CLOSED: return a <= x && x <= b; break;
                case boundary_types::OPEN: return a < x && x < b; break;
                default: return false;
            };
        }

    };

} // stf::math