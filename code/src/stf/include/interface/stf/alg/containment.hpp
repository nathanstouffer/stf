#pragma once

#include "stf/geom/aabb.hpp"
#include "stf/math/vector.hpp"

namespace stf::alg
{

    template<typename T, size_t N>
    inline bool contains(geom::aabb<T, N> const& box, math::vec<T, N> const& point)
    {
        return box.contains(point);
    }

    template<typename T, size_t N>
    inline bool contains(geom::aabb<T, N> const& lhs, geom::aabb<T, N> const& rhs)
    {
        return lhs.contains(rhs);
    }

} // stf::alg