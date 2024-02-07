#pragma once

#include "stf/math/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/polyline.hpp"
#include "stf/math/range.hpp"
#include "stf/math/segment.hpp"

namespace stf::alg
{

    template<typename T>
    inline bool intersect(math::range<T> const& lhs, math::range<T> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T, size_t N>
    inline bool intersect(math::aabb<T, N> const& lhs, math::aabb<T, N> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T>
    inline bool intersect(math::segment2<T> const& lhs, math::segment2<T> const& rhs)
    {
        // TODO (stouff) possibly wait to compute these until we know if the segments are colinear?
        bool const x_overlap = intersect(lhs.range(0), rhs.range(0));
        bool const y_overlap = intersect(lhs.range(1), rhs.range(1));
        if (x_overlap && y_overlap)
        {
            math::vec2<T> const& a = lhs.a; math::vec2<T> const& b = lhs.b;
            math::vec2<T> const& c = rhs.a; math::vec2<T> const& d = rhs.b;

            // compute which side of the lhs each point is on
            T const c_side = math::orientation(a, b, c);
            T const d_side = math::orientation(a, b, d);

            if (c_side == math::constants<T>::zero && d_side == math::constants<T>::zero)   // if all four points are colinear
            {
                return x_overlap && y_overlap;
            }
            else    // the general case where not all four points are colinear
            {
                T const a_side = math::orientation(c, d, a);
                T const b_side = math::orientation(c, d, b);
                return (c_side * d_side <= math::constants<T>::zero) && (a_side * b_side <= math::constants<T>::zero);
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    bool intersect(math::aabb2<T> const& aabb, math::segment2<T> const& segment)
    {
        // if either point is in the box, there is certainly an intersection
        if (aabb.contains(segment.a) || aabb.contains(segment.b)) { return true; }

        // TODO (stouff) write the rest of this function
    }

    template<typename T>
    inline bool intersect(math::segment2<T> const& segment, math::aabb2<T> const& aabb)
    {
        return intersect(aabb, segment);
    }

    template<typename T>
    bool intersect(math::aabb2<T> const& aabb, math::polyline2<T> const& polyline)
    {
        if (!polyline.is_empty() && aabb.intersects(polyline.aabb()))
        {
            for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all edges checking for intersection
            {
                if (intersect(aabb, polyline.edge(i))) { return true; }
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersect(math::polyline2<T> const& polyline, math::aabb2<T> const& aabb)
    {
        return intersect(aabb, polyline);
    }

} // stf::alg