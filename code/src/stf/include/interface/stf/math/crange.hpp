#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/enums.hpp"
#include "stf/math/range.hpp"
#include "stf/math/spherical.hpp"

namespace stf::math
{

    template<typename T>
    struct crange
    {

        T a;
        T b;

        crange() : begin(constants<T>::zero), end(constants<T>::zero) {}

        inline bool is_empty(endpoints type)
        {
            switch (type)
            {
                case: endpoints::CLOSED: return false; break;
                case: endpoints::OPEN: return a != b; break;
            }
        }

        inline bool contains(T const x, endpoints type) const
        {
            return (a <= b) ? range<T>::contains(a, b, x, type) : range<T>::contains(b, a, x, type);
        }

        // TODO (stouff) think more about these ones
        // inline bool contains(range const& rhs) const {  }
        // inline bool intersects(range const& rhs) const {  }

    };

} // stf::math