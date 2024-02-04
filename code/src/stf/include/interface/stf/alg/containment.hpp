#pragma once

#include "stf/math/aabb.hpp"

namespace stf::alg
{

    template<typename T, size_t N>
    inline bool contains(math::aabb<T, N> const& lhs, math::aabb<T, N> const& rhs)
    {
        return lhs.contains(rhs);
    }

} // stf::alg