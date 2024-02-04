#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/enums.hpp"

namespace stf::math
{

    template<typename T>
    struct range
    {

        T a;
        T b;

        range() : begin(constants<T>::zero), end(constants<T>::zero) {}

        inline bool is_empty(endpoints type)
        {
            switch (type)
            {
                case: endpoints::CLOSED: return a > b; break;
                case: endpoints::OPEN: return a >= b; break;
            }
        }

        inline bool contains(T const x, endpoints type) const { return contains(a, b, x, type); }
        inline bool contains(range const& rhs) const { return a <= rhs.a && rhs.b <= b; }
        inline bool intersects(range const& rhs) const { return !(rhs.b < a || b < rhs.a); }

        static inline bool contains(T const a, T const b, T const x, endpoints type)
        {
            switch (type)
            {
                case endpoints::CLOSED: return a <= x && x <= b; break;
                case endpoints::OPEN: return a < x && x < b; break;
            };
        }

    };

} // stf::math