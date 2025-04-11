#pragma once

#include "stf/geom/segment.hpp"
#include "stf/geom/polyline.hpp"

/**
 * @file clipping.hpp
 * @brief A file containing functions that clip geometric objects
 */

/// @cond DELETED
namespace stf::alg::guts
{

    enum region_code : int
    {
        INSIDE = 0x0,
        LEFT   = 0x1,
        RIGHT  = 0x2,
        BOTTOM = 0x4,
        TOP    = 0x8,
    };

    template<typename T>
    region_code code(geom::aabb2<T> const& box, math::vec2<T> const& point)
    {
        region_code x = region_code::INSIDE;
        if      (point.x < box.min.x) { x = region_code::LEFT;  }
        else if (box.max.x < point.x) { x = region_code::RIGHT; }

        region_code y = region_code::INSIDE;
        if      (point.y < box.min.y) { y = region_code::BOTTOM; }
        else if (box.max.y < point.y) { y = region_code::TOP;  }

        return static_cast<region_code>(x | y);
    }

}
/// @endcond

namespace stf::alg
{

    /**
     * @brief Clip a line segment to a bounding box
     * @tparam T Number type (float) 
     * @param [in] box
     * @param [in,out] seg 
     * @return Whether or not the segment should be accepted
     * @todo possibly refactor this to return a std::optional<geom::segment2<T>>
     * @todo possibly rename this to include the name of the algorithm (cohen-sutherland)
     * @todo possibly add the liang-barsky clipping algorithm as well
     */
    template<typename T>
    bool clip(geom::aabb2<T> const& box, geom::segment2<T>& seg)
    {
        guts::region_code code0 = guts::code(box, seg.a);
        guts::region_code code1 = guts::code(box, seg.b);

        // the official algorithm uses an infinite loop here, but there are certain inputs with floating-point precision issues that cause
        // the loop to never terminate in practice. 4 is the maximum number of iterations that should ever occur
        for (size_t i = 0; i < 4; ++i)
        {
            bool outside = code0 | code1;
            if (!outside)           // if both points are inside the box, accept the segment
            {
                return true;
            }
            else if (code0 & code1) // if both points share a region, reject the segment
            {
                return false;
            }
            else                    // otherwise, pick a point and clip it to a line defined by the box
            {
                math::vec2<T> point;
                guts::region_code code = code1 > code0 ? code1 : code0;
                if (code & guts::region_code::TOP)
                {
                    point.x = seg.a.x + (box.max.y - seg.a.y) * seg.slope_inv();
                    point.y = box.max.y;
                }
                else if (code & guts::region_code::BOTTOM)
                {
                    point.x = seg.a.x + (box.min.y - seg.a.y) * seg.slope_inv();
                    point.y = box.min.y;
                }
                else if (code & guts::region_code::RIGHT)
                {
                    point.x = box.max.x;
                    point.y = seg.a.y + (box.max.x - seg.a.x) * seg.slope();
                }
                else if (code & guts::region_code::LEFT)
                {
                    point.x = box.min.x;
                    point.y = seg.a.y + (box.min.x - seg.a.x) * seg.slope();
                }

                // update the segment endpoint
                if (code == code0)
                {
                    seg.a = point;
                    code0 = guts::code(box, seg.a);
                }
                else
                {
                    seg.b = point;
                    code1 = guts::code(box, seg.b);
                }
            }
        }
        return false;
    }

    /**
     * @brief Clip a polyline to a bounding box
     * @tparam T Number type (float)
     * @param [in] box 
     * @param [in] polyline 
     * @return A (possibly empty) std::vector of polylines clipped to @p box
     */
    template<typename T>
    std::vector<geom::polyline2<T>> clip(geom::aabb2<T> const& box, geom::polyline2<T> const& polyline)
    {
        std::vector<geom::polyline2<T>> clipped;

        geom::polyline2<T> sub_polyline;
        for (size_t i = 0; i + 1 < polyline.size(); ++i)
        {
            geom::segment2<T> edge = polyline.edge(i);
            if (clip(box, edge))                            // segment intersects the box => test how to add the segment to the clipped result
            {
                if (sub_polyline.is_empty())                // this is the a fresh polyline => add both points
                {
                    sub_polyline.push_back(edge.a);
                    sub_polyline.push_back(edge.b);
                }
                else if (sub_polyline.back() == edge.a)     // this segment should be added on to the existing polyline => only add the second point
                {
                    sub_polyline.push_back(edge.b);
                }
                else                                        // this segment is part of a new polyline => store the old polyline and start a new one
                {
                    clipped.push_back(sub_polyline);

                    sub_polyline.clear();
                    sub_polyline.push_back(edge.a);
                    sub_polyline.push_back(edge.b);
                }
            }
            else if (!sub_polyline.is_empty())              // segment does not intersect the box => immediately add the current sub_polyline to the result
            {
                clipped.push_back(sub_polyline);
                sub_polyline.clear();
            }
        }

        // edge case to check if the final sub_polyline was not added to the result
        if (!sub_polyline.is_empty())
        {
            clipped.push_back(sub_polyline);
        }

        return clipped;
    }

} // stf::alg