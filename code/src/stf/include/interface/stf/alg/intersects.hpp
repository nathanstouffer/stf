#pragma once

#include "stf/cam/frustum.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/hyperplane.hpp"
#include "stf/geom/obb.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/geom/ray.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"

/**
 * @file intersects.hpp
 * @brief A file containing functions that report whether or not two geometric objects intersect
 */

namespace stf::alg
{

    /**
     * @brief Compute whether or not two intervals intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs 
     * @param [in] rhs 
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    inline bool intersects(math::interval<T> const& lhs, math::interval<T> const& rhs)
    {
        return lhs.intersects(rhs);
    }

    /**
     * @brief Compute whether or not two aabbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T, size_t N>
    inline bool intersects(geom::aabb<T, N> const& lhs, geom::aabb<T, N> const& rhs)
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
    inline bool intersects(geom::obb2<T> const& lhs, geom::obb2<T> const& rhs)
    {
        return geom::intersects(lhs, rhs);
    }

    /**
     * @brief Compute whether or not two 3D obbs intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    inline bool intersects(geom::obb3<T> const& lhs, geom::obb3<T> const& rhs)
    {
        return geom::intersects(lhs, rhs);
    }

    /**
     * @brief Compute whether or not two segment2s intersect
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs intersects @p rhs
     */
    template<typename T>
    inline bool intersects(geom::segment2<T> const& lhs, geom::segment2<T> const& rhs)
    {
        math::vec2<T> const& a = lhs.a; math::vec2<T> const& b = lhs.b;
        math::vec2<T> const& c = rhs.a; math::vec2<T> const& d = rhs.b;

        // compute which side of the lhs each point is on
        T const c_side = math::orientation(a, b, c);
        T const d_side = math::orientation(a, b, d);

        if (c_side == math::constants<T>::zero && d_side == math::constants<T>::zero)   // if all four points are colinear
        {
            bool const x_overlap = intersects(lhs.interval(0), rhs.interval(0));
            bool const y_overlap = intersects(lhs.interval(1), rhs.interval(1));
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
     * @return Whether or not @p segment intersects @p aabb
     */
    template<typename T>
    bool intersects(geom::segment2<T> const& segment, geom::aabb2<T> const& aabb)
    {
        // if either point is in the box, there is certainly an intersection
        if (aabb.contains(segment.a) || aabb.contains(segment.b)) { return true; }

        // both points are outside the box => an intersection can only occur if the segment crosses a diagonal
        geom::segment2<T> const diagonal_0(aabb.min, aabb.max);
        if (intersects(segment, diagonal_0)) { return true; }

        math::vec2<T> const a(aabb.min.x, aabb.max.y);
        math::vec2<T> const b(aabb.max.x, aabb.min.y);
        geom::segment2<T> const diagonal_1(a, b);
        if (intersects(segment, diagonal_1)) { return true; }
        
        return false;       // fallthrough to return false
    }

    /**
     * @brief Compute whether or not a aabb and a segment2 intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] segment
     * @return Whether or not @p aabb intersects @p segment
     */
    template<typename T>
    inline bool intersects(geom::aabb2<T> const& aabb, geom::segment2<T> const& segment)
    {
        return intersects(segment, aabb);
    }

    /**
     * @brief Compute whether or not a polyline2 and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] polyline
     * @param [in] aabb
     * @return Whether or not @p polyline intersects @p aabb
     */
    template<typename T>
    bool intersects(geom::polyline2<T> const& polyline, geom::aabb2<T> const& aabb)
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

    /**
     * @brief Compute whether or not an aabb and a polyline2 intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] polyline
     * @return Whether or not @p aabb intersects @p polyline
     */
    template<typename T>
    inline bool intersects(geom::aabb2<T> const& aabb, geom::polyline2<T> const& polyline)
    {
        return intersects(polyline, aabb);
    }

    /**
     * @brief Compute whether or not a polygon and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] aabb
     * @return Whether or not @p polygon intersects @p aabb
     */
    template<typename T>
    bool intersects(geom::polygon<T> const& polygon, geom::aabb2<T> const& aabb)
    {
        if (!polygon.is_empty() && aabb.intersects(polygon.aabb()))
        {
            // if a point from either is contained in the other, they certainly intersect
            if (aabb.contains(polygon[0]) || polygon.contains(aabb.vertex(0), boundary_types::closed))
            {
                return true;
            }
            else
            {
                for (size_t i = 0; i < polygon.size(); ++i)    // iterate over all edges checking for intersection
                {
                    if (intersects(aabb, polygon.edge(i))) { return true; }
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
     * @return Whether or not @p aabb intersects @p polygon
     */
    template<typename T>
    inline bool intersects(geom::aabb2<T> const& aabb, geom::polygon<T> const& polygon)
    {
        return intersects(polygon, aabb);
    }

    /**
     * @brief Compute whether or not a polygon and a segment2 intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] segment
     * @return Whether or not @p polygon intersects @p segment
     */
    template<typename T>
    bool intersects(geom::polygon<T> const& polygon, geom::segment2<T> const& segment)
    {
        if (!polygon.is_empty() && polygon.aabb().intersects(segment.aabb()))
        {
            // if the polygon contains either point, they certainly intersect
            if (polygon.contains(segment.a, boundary_types::closed) || polygon.contains(segment.b, boundary_types::closed))
            {
                return true;
            }
            else
            {
                for (size_t i = 0; i < polygon.size(); ++i)    // iterate over all edges checking for intersection
                {
                    if (intersects(segment, polygon.edge(i))) { return true; }
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
     * @return Whether or not @p segment intersects @p polygon
     */
    template<typename T>
    inline bool intersects(geom::segment2<T> const& segment, geom::polygon<T> const& polygon)
    {
        return intersects(polygon, segment);
    }

    /**
     * @brief Compute whether or not a polygon and a polyline intersect
     * @tparam T Number type (eg float)
     * @param [in] polygon
     * @param [in] polyline
     * @return Whether or not @p polygon intersects @p polyline
     */
    template<typename T>
    bool intersects(geom::polygon<T> const& polygon, geom::polyline2<T> const& polyline)
    {
        if (!polygon.is_empty() && !polyline.is_empty() && polygon.aabb().intersects(polyline.aabb()))
        {
            for (size_t i = 0; i + 1 < polyline.size(); ++i)    // iterate over all edges checking for intersection
            {
                if (intersects(polygon, polyline.edge(i))) { return true; }
            }
        }
        return false;       // fallthrough to return false
    }

    /**
     * @brief Compute whether or not a polyline and a polygon intersect
     * @tparam T Number type (eg float)
     * @param [in] polyline
     * @param [in] polygon
     * @return Whether or not @p polyline intersects @p polygon
     */
    template<typename T>
    inline bool intersects(geom::polyline2<T> const& polyline, geom::polygon<T> const& polygon)
    {
        return intersects(polygon, polyline);
    }

    /**
     * @brief Compute whether or not a ray and a plane intersect
     * @tparam T Number type (eg float)
     * @param [in] ray
     * @param [in] plane
     * @return Whether or not @p ray intersects @p plane
     */
    template<typename T>
    bool intersects(geom::ray3<T> const& ray, geom::plane<T> const& plane)
    {
        T const signed_dist = plane.signed_dist(ray.origin);
        T const dot = ray.direction.dot(plane.normal());
        if (signed_dist == math::constants<T>::zero)        // if the origin of the ray is on the plane, then they certainly intersect
        {
            return true;
        }
        else if (dot == math::constants<T>::zero)           // if the normal and the ray are orthogonal, they do not intersect
        {
            return false;
        }
        else
        {
            // we now know that the origin of the ray is not on plane and the ray is not parallel to the
            // plane. this means that both signed_dist and dot are non-zero. if the signs of those values
            // are opposite, then the ray and the plane intersect
            return std::signbit(signed_dist) != std::signbit(dot);
        }
    }

    /**
     * @brief Compute whether or not a plane and a ray intersect
     * @tparam T Number type (eg float)
     * @param [in] plane
     * @param [in] ray
     * @return Whether or not @p plane intersects @p ray
     */
    template<typename T>
    inline bool intersects(geom::plane<T> const& plane, geom::ray3<T> const& ray)
    {
        return intersects(ray, plane);
    }

    /**
     * @brief Compute whether or not a frustum and an aabb intersect
     * @tparam T Number type (eg float)
     * @note This function reports false positives for some inputs (returns true for inputs that do not actually intersect)
     * @param [in] frustum
     * @param [in] aabb
     * @return Whether or not @p frustum intersects @p aabb
     */
    template<typename T>
    inline bool intersects_fast(cam::frustum<T> const& frustum, geom::aabb3<T> const& aabb)
    {
        return frustum.intersects_fast(aabb);
    }

    /**
     * @brief Compute whether or not an aabb and a frustum intersect
     * @note This function reports false positives for some inputs (returns true for inputs that do not actually intersect)
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] frustum
     * @return Whether or not @p aabb intersects @p frustum
     */
    template<typename T>
    inline bool intersects_fast(geom::aabb3<T> const& aabb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects_fast(aabb);
    }

    /**
     * @brief Compute whether or not a frustum and an aabb intersect
     * @tparam T Number type (eg float)
     * @param [in] frustum
     * @param [in] aabb
     * @return Whether or not @p frustum intersects @p aabb
     */
    template<typename T>
    inline bool intersects(cam::frustum<T> const& frustum, geom::aabb3<T> const& aabb)
    {
        return frustum.intersects(aabb);
    }

    /**
     * @brief Compute whether or not an aabb and a frustum intersect
     * @tparam T Number type (eg float)
     * @param [in] aabb
     * @param [in] frustum
     * @return Whether or not @p aabb intersects @p frustum
     */
    template<typename T>
    inline bool intersects(geom::aabb3<T> const& aabb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects(aabb);
    }

    /**
     * @brief Compute whether or not a frustum and an obb intersect
     * @tparam T Number type (eg float)
     * @param [in] frustum
     * @param [in] obb
     * @return Whether or not @p frustum intersects @p obb
     */
    template<typename T>
    inline bool intersects(cam::frustum<T> const& frustum, geom::obb3<T> const& obb)
    {
        return frustum.intersects(obb);
    }

    /**
     * @brief Compute whether or not an obb and a frustum intersect
     * @tparam T Number type (eg float)
     * @param [in] obb
     * @param [in] frustum
     * @return Whether or not @p obb intersects @p frustum
     */
    template<typename T>
    inline bool intersects(geom::obb3<T> const& obb, cam::frustum<T> const& frustum)
    {
        return frustum.intersects(obb);
    }

} // stf::alg