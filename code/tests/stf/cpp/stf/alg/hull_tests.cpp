#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/alg/hull.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::alg
{

TEST(hull, convex_hull_fixed_points)
{
    // TODO (stouff) write tests with edge cases here
    //std::vector<scaffolding::alg::hull::convex_hull_fixed_points<float>> tests = {
    //};
    //scaffolding::verify(tests);
}

TEST(hull, convex_hull_random_points)
{
    std::vector<scaffolding::alg::hull::convex_hull_random_points<float>> tests = {
        { 0, 10 },
        { 0, 100 },
        { 1, 50 },
        { 2, 500 },
        { -1, 2000 },
    };
    scaffolding::verify(tests);
}

} // namespace stf::alg