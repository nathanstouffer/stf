
#ifndef STF_SCAFFOLDING_ALG_HULL_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_ALG_HULL_HPP_HEADER_GUARD

#include <random>

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/hull.hpp>

namespace stf::scaffolding::alg::hull
{

template <typename T>
struct convex_hull_fixed_points
{
    stf::geom::holygon<T> input;
    stf::geom::polygon<T> expected;

    void verify(size_t const i) const
    {
        stf::geom::polygon<T> actual = stf::alg::convex_hull(input);

        ASSERT_TRUE(actual.is_convex()) << info(i) << "Failed to compute a hull that is convex";
        // TODO (stouff) test winding order
        ASSERT_EQ(expected, actual) << info(i) << "Failed to compute correct hull";
    }
};

template <typename T>
struct convex_hull_random_points
{
    int seed;
    int count;

    void verify(size_t const i) const
    {
        // TODO (stouff) generate random points
        std::vector<stf::math::vec2<T>> points;
        {
            points.reserve(count);

            std::mt19937 gen(seed);
            std::uniform_real_distribution<T> dist(-100.f, 100.f);

            for (int p = 0; p < count; ++p)
            {
                stf::math::vec2<T> point(dist(gen), dist(gen));
                points.push_back(point);
            }
        }

        stf::geom::polygon<T> hull = stf::alg::convex_hull(points);

        ASSERT_TRUE(hull.is_convex()) << info(i) << "Failed to compute a hull that is convex";

        std::vector<math::vec2<T>> const& vertices = hull.vertices();
        T orientation = math::orientation(vertices[0], vertices[1], vertices[2]);
        ASSERT_LT(math::constants<T>::zero, orientation) << "Failed to have correct orientation";

        for (stf::math::vec2<T> const& p : points)
        {
            ASSERT_TRUE(hull.contains(p, stf::boundary_types::closed))
                << info(i) << "Failed to contain a point of the input";
        }
    }
};

} // namespace stf::scaffolding::alg::hull

#endif