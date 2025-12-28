#ifndef STF_ALG_CLIPPING_HPP_HEADER_GUARD
#define STF_ALG_CLIPPING_HPP_HEADER_GUARD

#include "stf/geom/segment.hpp"
#include "stf/geom/polyline.hpp"

/**
 * @file clipping.hpp
 * @brief A file containing functions that clip geometric objects
 */

/// @cond DELETED
namespace stf::alg::guts
{

enum class region_code : int
{
    inside = 0x0,
    left = 0x1,
    right = 0x2,
    bottom = 0x4,
    top = 0x8,
};

constexpr region_code operator|(region_code lhs, region_code rhs)
{
    return static_cast<region_code>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

constexpr region_code operator&(region_code lhs, region_code rhs)
{
    return static_cast<region_code>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

constexpr bool has_flag(region_code value, region_code query)
{
    return (value & query) != region_code::inside;
}

template <typename T>
region_code code(geom::aabb2<T> const& box, math::vec2<T> const& point)
{
    region_code x = region_code::inside;
    if (point.x < box.min.x)
    {
        x = region_code::left;
    }
    else if (box.max.x < point.x)
    {
        x = region_code::right;
    }

    region_code y = region_code::inside;
    if (point.y < box.min.y)
    {
        y = region_code::bottom;
    }
    else if (box.max.y < point.y)
    {
        y = region_code::top;
    }

    return static_cast<region_code>(x | y);
}

} // namespace stf::alg::guts
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
template <typename T>
bool clip(geom::aabb2<T> const& box, geom::segment2<T>& seg)
{
    guts::region_code code0 = guts::code(box, seg.a);
    guts::region_code code1 = guts::code(box, seg.b);

    // the official algorithm uses an infinite loop here, but there are certain inputs with floating-point precision
    // issues that cause the loop to never terminate in practice. 4 is the maximum number of iterations that should ever
    // occur
    for (size_t i = 0; i < 4; ++i)
    {
        bool outside = (code0 | code1) != guts::region_code::inside;
        if (!outside) // if both points are inside the box, accept the segment
        {
            return true;
        }
        else if (guts::has_flag(code0, code1)) // if both points share a region, reject the segment
        {
            return false;
        }
        else // otherwise, pick a point and clip it to a line defined by the box
        {
            math::vec2<T> point;
            guts::region_code code = code1 > code0 ? code1 : code0;
            if (guts::has_flag(code, guts::region_code::top))
            {
                point.x = seg.a.x + (box.max.y - seg.a.y) * seg.slope_inv();
                point.y = box.max.y;
            }
            else if (guts::has_flag(code, guts::region_code::bottom))
            {
                point.x = seg.a.x + (box.min.y - seg.a.y) * seg.slope_inv();
                point.y = box.min.y;
            }
            else if (guts::has_flag(code, guts::region_code::right))
            {
                point.x = box.max.x;
                point.y = seg.a.y + (box.max.x - seg.a.x) * seg.slope();
            }
            else if (guts::has_flag(code, guts::region_code::left))
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
template <typename T>
std::vector<geom::polyline2<T>> clip(geom::aabb2<T> const& box, geom::polyline2<T> const& polyline)
{
    std::vector<geom::polyline2<T>> clipped;

    geom::polyline2<T> sub_polyline;
    for (size_t i = 0; i + 1 < polyline.size(); ++i)
    {
        geom::segment2<T> edge = polyline.edge(i);
        if (clip(box, edge)) // segment intersects the box => test how to add the segment to the clipped result
        {
            if (sub_polyline.is_empty()) // this is the a fresh polyline => add both points
            {
                sub_polyline.push_back(edge.a);
                sub_polyline.push_back(edge.b);
            }
            else if (sub_polyline.back() == edge.a) // add to existing polyline => only add the second point
            {
                sub_polyline.push_back(edge.b);
            }
            else // part of a new polyline => store the old polyline and start a new one
            {
                clipped.push_back(sub_polyline);

                sub_polyline.clear();
                sub_polyline.push_back(edge.a);
                sub_polyline.push_back(edge.b);
            }
        }
        else if (!sub_polyline.is_empty()) // segment does not intersect the box => immediately add the current
                                           // sub_polyline to the result
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

} // namespace stf::alg

#endif