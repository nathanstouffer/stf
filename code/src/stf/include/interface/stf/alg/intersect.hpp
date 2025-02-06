#pragma once

#include "stf/cam/frustum.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/obb.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"

/**
 * @file intersect.hpp
 * @brief A file containing functions that report whether or not two geometric objects intersect
 */

namespace stf::alg
{

    /**
     * @brief Compute whether or not two intervals intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs 
     * @param [in] rhs 
     * @return Whether or not the two intervals intersect
     */
    template<typename T>
    inline bool intersect(math::interval<T> const& lhs, math::interval<T> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    /**
     * @brief Compute whether or not two aabbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not the two aabbs intersect
     */
    template<typename T, size_t N>
    inline bool intersect(geom::aabb<T, N> const& lhs, geom::aabb<T, N> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    /**
     * @brief Compute whether or not two 2D obbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    inline bool const intersect(geom::obb2<T> const& lhs, geom::obb2<T> const& rhs)
    {
        return geom::intersect(lhs, rhs);
    }

    /**
     * @brief Compute whether or not two 3D obbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    inline bool const intersect(geom::obb3<T> const& lhs, geom::obb3<T> const& rhs)
    {
        return geom::intersect(lhs, rhs);
    }

    /**
     * @brief Compute whether or not two segment2s intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not the two segment2s intersect
     */
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
            bool const x_overlap = intersect(lhs.interval(0), rhs.interval(0));
            bool const y_overlap = intersect(lhs.interval(1), rhs.interval(1));
            return x_overlap && y_overlap;
        }
        else    // the general case where not all four points are colinear
        {
            T const a_side = math::orientation(c, d, a);
            T const b_side = math::orientation(c, d, b);
            return (c_side * d_side <= math::constants<T>::zero) && (a_side * b_side <= math::constants<T>::zero);
        }
    }

    /**
     * @brief Compute whether or not a segment2 and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] segment
     * @param [in] aabb
     * @return Whether or not a segment2 and an aabb intersect
     */
    template<typename T>
    bool intersect(geom::segment2<T> const& segment, geom::aabb2<T> const& aabb)
    {
        // if either point is in the box, there is certainly an intersection
        if (aabb.contains(segment.a) || aabb.contains(segment.b)) { return true; }

        // both points are outside the box => an intersection can only occur if the segment crosses a diagonal
        geom::segment2<T> const diagonal_0(aabb.min, aabb.max);
        if (intersect(segment, diagonal_0)) { return true; }

        math::vec2<T> const a(aabb.min.x, aabb.max.y);
        math::vec2<T> const b(aabb.max.x, aabb.min.y);
        geom::segment2<T> const diagonal_1(a, b);
        if (intersect(segment, diagonal_1)) { return true; }
        
        return false;       // fallthrough to return false
    }

    /**
     * @brief Compute whether or not a aabb and a segment2 intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] segment
     * @return Whether or not an aabb and a segment2 intersect
     */
    template<typename T>
    inline bool intersect(geom::aabb2<T> const& aabb, geom::segment2<T> const& segment)
    {
        return intersect(segment, aabb);
    }

    /**
     * @brief Compute whether or not a polyline2 and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] polyline
     * @param [in] aabb
     * @return Whether or not a polyline2 and an aabb intersect
     */
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

    /**
     * @brief Compute whether or not an aabb and a polyline2 intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] polyline
     * @return Whether or not an aabb and a polyline2 intersect
     */
    template<typename T>
    inline bool intersect(geom::aabb2<T> const& aabb, geom::polyline2<T> const& polyline)
    {
        return intersect(polyline, aabb);
    }

    /**
     * @brief Compute whether or not a polygon and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] aabb
     * @return Whether or not a polygon and an aabb intersect
     */
    template<typename T>
    bool intersect(geom::polygon<T> const& polygon, geom::aabb2<T> const& aabb)
    {
        if (!polygon.is_empty() && aabb.intersects(polygon.aabb()))
        {
            // if a point from either is contained in the other, they certainly intersect
            if (aabb.contains(polygon[0]) || polygon.contains(aabb.vertex(0), boundary_types::CLOSED))
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

    /**
     * @brief Compute whether or not an aabb and a polygon intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] polygon
     * @return Whether or not an aabb and a polygon intersect
     */
    template<typename T>
    inline bool intersect(geom::aabb2<T> const& aabb, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, aabb);
    }

    /**
     * @brief Compute whether or not a polygon and a segment2 intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] segment
     * @return Whether or not a polygon and a segment2 intersect
     */
    template<typename T>
    bool intersect(geom::polygon<T> const& polygon, geom::segment2<T> const& segment)
    {
        if (!polygon.is_empty() && polygon.aabb().intersects(segment.aabb()))
        {
            // if the polygon contains either point, they certainly intersect
            if (polygon.contains(segment.a, boundary_types::CLOSED) || polygon.contains(segment.b, boundary_types::CLOSED))
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

    /**
     * @brief Compute whether or not a segment2 and a polygonintersect
     * @tparam T Number type (eg float)
     * @param [in] segment
     * @param [in] polygon
     * @return Whether or not a segment2 and a polygon intersect
     */
    template<typename T>
    inline bool intersect(geom::segment2<T> const& segment, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, segment);
    }

    /**
     * @brief Compute whether or not a polygon and a polyline intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] polyline
     * @return Whether or not a polygon and a polyline intersect
     */
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

    /**
     * @brief Compute whether or not a polyline and a polygon intersect
     * @tparam T Number type (eg float)
     * @param [in] polyline
     * @param [in] polygon
     * @return Whether or not a polyline and a polygon intersect
     */
    template<typename T>
    inline bool intersect(geom::polyline2<T> const& polyline, geom::polygon<T> const& polygon)
    {
        return intersect(polygon, polyline);
    }

    /**
     * @brief Compute whether or not a frustum and an aabb intersect
     * @tparam T Number type (eg float)
     * @note This function reports false positives for some inputs (returns true for inputs that do not actually intersect)
     * @param [in] frustum
     * @param [in] aabb
     * @return Whether or not a frustum and an aabb intersect
     */
    template<typename T>
    inline bool intersect_fast(cam::frustum<T> const& frustum, geom::aabb3<T> const& aabb)
    {
        return frustum.intersects_fast(aabb);
    }

    /**
     * @brief Compute whether or not an aabb and a frustum intersect
     * @note This function reports false positives for some inputs (returns true for inputs that do not actually intersect)
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] frustum
     * @return Whether or not an aabb and a frustum intersect
     */
    template<typename T>
    inline bool intersect_fast(geom::aabb3<T> const& aabb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects_fast(aabb);
    }

    /**
     * @brief Compute whether or not a frustum and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] frustum
     * @param [in] aabb
     * @return Whether or not a frustum and an aabb intersect
     */
    template<typename T>
    inline bool intersect(cam::frustum<T> const& frustum, geom::aabb3<T> const& aabb)
    {
        return frustum.intersects(aabb);
    }

    /**
     * @brief Compute whether or not an aabb and a frustum intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] frustum
     * @return Whether or not an aabb and a frustum intersect
     */
    template<typename T>
    inline bool intersect(geom::aabb3<T> const& aabb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects(aabb);
    }

    /**
     * @brief Compute whether or not a frustum and an obb intersect
     * @tparam T Number type (eg float)
     * @param [in] frustum
     * @param [in] obb
     * @return Whether or not a frustum and an obb intersect
     */
    template<typename T>
    inline bool intersect(cam::frustum<T> const& frustum, geom::obb3<T> const& obb)
    {
        return frustum.intersects(obb);
    }

    /**
     * @brief Compute whether or not an obb and a frustum intersect
     * @tparam T Number type (eg float)
     * @param [in] obb
     * @param [in] frustum
     * @return Whether or not an obb and a frustum intersect
     */
    template<typename T>
    inline bool intersect(geom::obb3<T> const& obb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects(obb);
    }

} // stf::alg