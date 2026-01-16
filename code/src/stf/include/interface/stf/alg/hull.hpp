#ifndef STF_ALG_HULL_HPP_HEADER_GUARD
#define STF_ALG_HULL_HPP_HEADER_GUARD

#include <algorithm>

#include "stf/geom/polygon.hpp"

/**
 * @file hull.hpp
 * @brief A file containing functions that compute the convex hull of geometric objects
 */

/// @cond DELETED
namespace stf::alg::guts
{

template <typename T>
std::vector<math::vec2<T>> base_case_hull(std::vector<math::vec2<T>> const& points)
{
    std::vector<math::vec2<T>> hull;
    hull.reserve(points.size());
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    return hull;
}

} // namespace stf::alg::guts
/// @endcond DELETED

namespace stf::alg
{

/**
 * @brief Compute the convex hull of a set of points
 * @tparam T Number type (eg float)
 * @param input [in] The set of points
 * @return The convex hull as a ring of counter-clockwise points
 */
template <typename T>
std::vector<math::vec2<T>> convex_hull(std::vector<math::vec2<T>> const& input)
{
    if (input.size() < 3)
    {
        // the operator[] is valid because we know the size of input to be 2 in the third condition
        if (input.empty() || input.size() == 1 || input[0] != input[1])
        {
            return input;
        }
        else
        {
            return std::vector<math::vec2<T>>{input[0]};
        }
    }

    // first sort the points based on x-coordinate
    std::vector<math::vec2<T>> points = input;
    std::sort(points.begin(), points.end(),
              [](math::vec2<T> const& lhs, math::vec2<T> const& rhs) { return lhs.x < rhs.x; });

    // define upper and lower hulls
    std::vector<math::vec2<T>> upper = guts::base_case_hull(points);
    std::vector<math::vec2<T>> lower = guts::base_case_hull(points);

    // compute upper and lower hulls
    for (size_t i = 2; i < points.size(); ++i)
    {
        math::vec2<T> candidate = points[i];
        // TODO (stouff) probably move this to guts
        while (upper.size() >= 2 && math::orientation(*(upper.rbegin() + 1), *upper.rbegin(), candidate) >= 0)
        {
            upper.pop_back();
        }
        while (lower.size() >= 2 && math::orientation(*(lower.rbegin() + 1), *lower.rbegin(), candidate) <= 0)
        {
            lower.pop_back();
        }
        upper.push_back(candidate);
        lower.push_back(candidate);
    }

    // merge hulls
    std::vector<math::vec2<T>> hull;
    {
        hull.reserve(lower.size() + upper.size());
        hull.insert(hull.end(), lower.begin(), lower.end());
        if (upper.size() > 2)
        {
            hull.insert(hull.end(), upper.rbegin() + 1, upper.rend() - 1);
        }
    }

    return hull;
}

/**
 * @brief Compute the convex hull of a polygon
 * @tparam T Number type (eg float)
 * @param polygon [in] The polygon from which to compute the convex hull
 * @return The convex hull as a ring of counter-clockwise points
 */
template <typename T>
std::vector<math::vec2<T>> convex_hull(geom::polygon<T> const& polygon)
{
    return convex_hull(polygon.vertices());
}

/**
 * @brief Compute the convex hull of a holygon
 * @tparam T Number type (eg float)
 * @param holygon [in] The holygon from which to compute the convex hull
 * @return The convex hull as a ring of counter-clockwise points
 */
template <typename T>
std::vector<math::vec2<T>> convex_hull(geom::holygon<T> const& holygon)
{
    return convex_hull(holygon.hull());
}

} // namespace stf::alg

#endif