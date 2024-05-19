#pragma once

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"
#include "stf/math/spherical.hpp"

namespace stf::math
{

    template<typename T>
    struct cinterval final
    {

        T a;
        T b;

        cinterval() : a(constants<T>::zero), b(constants<T>::zero) {}
        cinterval(T const _a, T const _b) : a(_a), b(_b) {}

        inline bool is_empty(boundary_types type)
        {
            switch (type)
            {
                case boundary_types::CLOSED: return false; break;
                case boundary_types::OPEN: return a != b; break;
                default: return true;
            }
        }

        inline bool contains(T const x, boundary_types type) const
        {
            return (a <= b) ? interval<T>::contains(a, b, x, type) : !interval<T>::contains(b, a, x, complement(type));
        }

        // TODO think more about these ones
        // inline bool contains(interval const& rhs) const {  }
        // inline bool intersects(interval const& rhs) const {  }

    };

} // stf::math