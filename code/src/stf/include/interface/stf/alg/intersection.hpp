#pragma once

#include "stf/geom/aabb.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/range.hpp"

namespace stf::alg
{

    template<typename T>
    inline bool intersect(math::range<T> const& lhs, math::range<T> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T, size_t N>
    inline bool intersect(geom::aabb<T, N> const& lhs, geom::aabb<T, N> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    template<typename T>
    inline bool intersect(geom::segment2<T> const& lhs, geom::segment2<T> const& rhs)
    {
        math::vec2<T> const& a = lhs.a; math::vec2<T> const& b = lhs.b;
        math::vec2<T> const& c = rhs.a; math::vec2<T> const& d = rhs.b;

        // compute which side of the lhs each point is on
        T const c_side = math::orientation(a, b, c);
        T const d_side = math::orientation(a, b, d);

        if (c_side == math::constants<T>::zero && d_side == math::constants<T>::zero)   // if all four points are colinear
        {
            bool const x_overlap = intersect(lhs.range(0), rhs.range(0));
            bool const y_overlap = intersect(lhs.range(1), rhs.range(1));
            return x_overlap && y_overlap;
        }
        else    // the general case where not all four points are colinear
        {
            T const a_side = math::orientation(c, d, a);
            T const b_side = math::orientation(c, d, b);
            return (c_side * d_side <= math::constants<T>::zero) && (a_side * b_side <= math::constants<T>::zero);
        }
    }

    template<typename T>
    bool intersect(geom::segment2<T> const& segment, geom::aabb2<T> const& aabb)
    {
        // if either point is in the box, there is certainly an intersection
        if (aabb.contains(segment.a) || aabb.contains(segment.b)) { return true; }

        // iterate over each edge of the box and test if the segment intersects it
        for (size_t i = 0; i < 3; ++i)
        {
            // compute an edge of the bounding box
            math::vec2<T> const& a = aabb.vertex(i);
            math::vec2<T> const& b = aabb.vertex((i + 1) % 4);
            geom::segment2<T> edge(a, b);

            // if the segment intersects the edge then return true
            if (intersect(segment, edge)) { return true; }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersect(geom::aabb2<T> const& aabb, geom::segment2<T> const& segment)
    {
        return intersect(segment, aabb);
    }

    template<typename T>
    bool intersect(geom::polyline2<T> const& polyline, geom::aabb2<T> const& aabb)
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
    inline bool intersect(geom::aabb2<T> const& aabb, geom::polyline2<T> const& polyline)
    {
        return intersect(polyline, aabb);
    }

    template<typename T>
    bool intersect(geom::polygon<T> const& polygon, geom::aabb2<T> const& aabb)
    {
        if (!polygon.is_empty() && aabb.intersects(polygon.aabb()))
        {
            if (aabb.contains(polygon[0]) || polygon.contains(box[0]))  // if a point from either is contained in the other, they certainly intersect
            {
                return true;
            }
            else
            {
                for (size_t i = 0; i < polygon.size(); ++i)    // iterate over all edges checking for intersection
                {
                    if (intersect(aabb, polygon.edge(i))) { return true; }
                }
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersect(geom::aabb2<T> const& aabb, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, aabb);
    }

    template<typename T>
    bool intersect(geom::polygon<T> const& polygon, geom::segment2<T> const& segment)
    {
        if (!polygon.is_empty() && polygon.aabb().intersects(segment.aabb()))
        {
            if (polygon.contains(segment.a) || polygon.contains(segment.b))  // if the polygon contains either point, they certainly intersect
            {
                return true;
            }
            else
            {
                for (size_t i = 0; i < polygon.size(); ++i)    // iterate over all edges checking for intersection
                {
                    if (intersect(segment, polygon.edge(i))) { return true; }
                }
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersect(geom::segment2<T> const& segment, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, segment);
    }

    template<typename T>
    bool intersect(geom::polygon<T> const& polygon, geom::polyline2<T> const& polyline)
    {
        if (!polygon.is_empty() && !polyline.is_empty() && polygon.aabb().intersects(polyline.aabb()))
        {
            for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all edges checking for intersection
            {
                if (intersect(polygon, polyline.edge(i))) { return true; }
            }
        }
        return false;       // fallthrough to return false
    }

    template<typename T>
    inline bool intersect(geom::polyline2<T> const& polyline, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, polyline);
    }

} // stf::alg