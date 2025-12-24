#ifndef STF_SCAFFOLDING_ALG_CLIPPING_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_ALG_CLIPPING_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/clipping.hpp>

namespace stf::scaffolding::alg::clipping
{

template <typename T>
struct segment
{
    stf::geom::aabb2<T> box;
    stf::geom::segment2<T> input;
    bool accept;
    stf::geom::segment2<T> expected;

    void verify(size_t const i) const
    {
        stf::geom::segment2<T> clipped = input;
        ASSERT_EQ(accept, stf::alg::clip(box, clipped)) << info(i) << "Failed to accept/reject segment";

        if (accept)
        {
            ASSERT_EQ(expected, clipped) << info(i) << "Failed to clip segment";
        }

        stf::geom::segment2<T> flipped = stf::geom::segment2<T>(input.b, input.a);
        ASSERT_EQ(accept, stf::alg::clip(box, flipped)) << info(i) << "Failed to accept/reject flipped segment";

        if (accept)
        {
            stf::geom::segment2<T> flipped_clipped = stf::geom::segment2<T>(expected.b, expected.a);
            ASSERT_EQ(flipped_clipped, flipped) << info(i) << "Failed to clip flipped segment";
        }
    }
};

template <typename T>
struct polyline
{
    stf::geom::aabb2<T> box;
    stf::geom::polyline2<T> input;
    std::vector<geom::polyline2<T>> expected;

    void verify(size_t const index) const
    {
        std::vector<stf::geom::polyline2<T>> clipped = stf::alg::clip(box, input);

        ASSERT_EQ(expected.size(), clipped.size())
            << info(index) << "Failed to clip polyline to correct number of sub-polylines";
        for (size_t i = 0; i < expected.size(); ++i)
        {
            ASSERT_EQ(expected[i], clipped[i])
                << info(index) << "Failed equality test for " << i << "th clipped sub-polyline";
        }
    }
};

} // namespace stf::scaffolding::alg::clipping

#endif