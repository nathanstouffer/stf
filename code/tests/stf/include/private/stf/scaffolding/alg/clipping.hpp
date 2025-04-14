#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/clipping.hpp>

namespace stf::scaffolding::alg::clipping
{

    template<typename T>
    struct segment
    {
        geom::aabb2<T> box;
        geom::segment2<T> input;
        bool accept;
        geom::segment2<T> clipped;
    };

    template<typename T>
    void verify(segment<T> const& test)
    {
        geom::segment2<T> clipped = test.input;
        ASSERT_EQ(test.accept, alg::clip(test.box, clipped)) << "Failed to accept/reject segment";

        if (test.accept)
        {
            ASSERT_EQ(test.clipped, clipped) << "Failed to clip segment";
        }

        geom::segment2<T> flipped = geom::segment2<T>(test.input.b, test.input.a);
        ASSERT_EQ(test.accept, alg::clip(test.box, flipped)) << "Failed to accept/reject flipped segment";

        if (test.accept)
        {
            geom::segment2<T> flipped_clipped = geom::segment2<T>(test.clipped.b, test.clipped.a);
            ASSERT_EQ(flipped_clipped, flipped) << "Failed to clip flipped segment";
        }
    }

    template<typename T>
    struct polyline
    {
        geom::aabb2<T> box;
        geom::polyline2<T> input;
        std::vector<geom::polyline2<T>> clipped;
    };

    template<typename T>
    void verify(polyline<T> const& test)
    {
        std::vector<geom::polyline2<T>> clipped = alg::clip(test.box, test.input);

        ASSERT_EQ(test.clipped.size(), clipped.size()) << "Failed to clip polyline to correct number of sub-polylines";
        for (size_t i = 0; i < test.clipped.size(); ++i)
        {
            ASSERT_EQ(test.clipped[i], clipped[i]) << "Failed equality test for " << i << "th clipped sub-polyline";
        }
    }

} // stf::scaffolding::alg::clipping