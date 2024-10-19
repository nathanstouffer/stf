#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/clipping.hpp>

namespace stf::alg::scaffolding::clipping
{

    template<typename T>
    struct segment
    {
        geom::aabb2<T> const box;
        geom::segment2<T> const input;
        bool const accept;
        geom::segment2<T> const clipped;
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
    }

    template<typename T>
    struct polyline
    {
        geom::aabb2<T> const box;
        geom::polyline2<T> const input;
        std::vector<geom::polyline2<T>> const clipped;
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

} // stf::alg::scaffolding::clipping