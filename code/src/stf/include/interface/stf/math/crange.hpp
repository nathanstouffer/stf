#pragma once

#include "stf/enums.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/range.hpp"
#include "stf/math/spherical.hpp"

namespace stf::math
{

    template<typename T>
    struct crange final
    {

        T a;
        T b;

        crange() : a(constants<T>::zero), b(constants<T>::zero) {}
        crange(T const _a, T const _b) : a(_a), b(_b) {}

        inline bool is_empty(boundary type)
        {
            switch (type)
            {
                case boundary::CLOSED: return false; break;
                case boundary::OPEN: return a != b; break;
                default: return true;
            }
        }

        inline bool contains(T const x, boundary type) const
        {
            return (a <= b) ? range<T>::contains(a, b, x, type) : !range<T>::contains(b, a, x, complement(type));
        }

        // TODO think more about these ones
        // inline bool contains(range const& rhs) const {  }
        // inline bool intersects(range const& rhs) const {  }

    };

} // stf::math