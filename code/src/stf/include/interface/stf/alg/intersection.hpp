#pragma once

#include "stf/math/aabb.hpp"
#include "stf/math/polyline.hpp"
#include "stf/math/range.hpp"
#include "stf/math/segment.hpp"

namespace stf::alg
{

    template<typename T>
    inline bool intersects(math::range<T> const& lhs, math::range<T> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T, size_t N>
    inline bool intersects(math::aabb<T, N> const& lhs, math::aabb<T, N> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T>
    inline bool intersects(math::segment2<T> const& lhs, math::segment2<T> const& rhs)
    {
        bool x_overlap = intersects(lhs.range(0), rhs.range(0));
        bool y_overlap = intersects(lhs.range(1), rhs.range(1));
        if (x_overlap && y_overlap)
        {
            vec_t const& a = lhs.a; vec_t const& b = rhs.b;
            vec_t const& c = lhs.a; vec_t const& d = rhs.b;

            // compute which side of the lhs each point is on
            T const c_side = math::orientation(a, b, c);
            T const d_side = math::orientation(a, b, d);

            // TODO (stouff) finish writing this function
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    bool intersects(math::aabb2<T> const& aabb, math::segment2<T> const& segment)
    {
        // if either point is in the box, there is certainly an intersection
        if (aabb.contains(segment.a) || aabb.contains(segment.b)) { return true; }

        // TODO (stouff) write the rest of this function
    }

    template<typename T>
    inline bool intersects(math::segment2<T> const& segment, math::aabb2<T> const& aabb)
    {
        return intersects(aabb, segment);
    }

    template<typename T>
    bool intersects(math::aabb2<T> const& aabb, math::polyline2<T> const& polyline)
    {
        if (!polyline.is_empty() && aabb.intersects(polyline.aabb()))
        {
            for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all edges checking for intersection
            {
                if (intersects(aabb, polyline.edge(i))) { return true; }
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersects(math::polyline2<T> const& polyline, math::aabb2<T> const& aabb)
    {
        return intersects(aabb, polyline);
    }

} // stf::alg