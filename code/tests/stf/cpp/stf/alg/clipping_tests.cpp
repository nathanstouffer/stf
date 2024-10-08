#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/alg/scaffolding/clipping.hpp"

namespace stf::alg
{

    TEST(clipping, segment)
    {
        stff::aabb2 box(stff::vec2(10), stff::vec2(20));
        stff::segment2 irrelevent(stff::vec2(0), stff::vec2(0));
        std::vector<scaffolding::clipping::segment<float>> tests =
        {
            // segments entirely in the box
            { box, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 19)), true, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 19)) },
            { box, stff::segment2(stff::vec2(11, 19), stff::vec2(19, 11)), true, stff::segment2(stff::vec2(11, 19), stff::vec2(19, 11)) },
            { box, stff::segment2(stff::vec2(11, 11), stff::vec2(11, 19)), true, stff::segment2(stff::vec2(11, 11), stff::vec2(11, 19)) },
            { box, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 11)), true, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 11)) },
            // segments with both endpoints outside the box that do intersect the box
            { box, stff::segment2(stff::vec2( 9, 11), stff::vec2(21, 11)), true, stff::segment2(stff::vec2(10, 11), stff::vec2(20, 11)) },
            { box, stff::segment2(stff::vec2(11,  9), stff::vec2(11, 21)), true, stff::segment2(stff::vec2(11, 10), stff::vec2(11, 20)) },
            { box, stff::segment2(stff::vec2( 9,  9), stff::vec2(21, 21)), true, stff::segment2(stff::vec2(10, 10), stff::vec2(20, 20)) },
            { box, stff::segment2(stff::vec2( 9, 21), stff::vec2(21,  9)), true, stff::segment2(stff::vec2(10, 20), stff::vec2(20, 10)) },
            { box, stff::segment2(stff::vec2( 9, 21), stff::vec2(21,  9)), true, stff::segment2(stff::vec2(10, 20), stff::vec2(20, 10)) },
            // segments that do not intersect the box
            { box, stff::segment2(stff::vec2( 4, 15), stff::vec2(15,  4)), false, irrelevent},
        };

        for (scaffolding::clipping::segment<float> const& test : tests)
        {
            scaffolding::clipping::verify(test);
        }
    }

} // stf::alg