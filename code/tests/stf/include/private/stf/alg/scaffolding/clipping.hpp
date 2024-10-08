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

} // stf::alg::scaffolding::clipping