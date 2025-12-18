#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/geom/polygon.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::geom
{
    
    TEST(polygon, is_convex)
    {
        std::vector<scaffolding::geom::polygon::is_convex<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(2, -2) }), false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(3, 0), stff::vec2(4, 4) }), false },
        };
        scaffolding::verify(tests);
    }

    TEST(polygon, signed_area)
    {
        std::vector<scaffolding::geom::polygon::signed_area<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), 1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(0, 1), stff::vec2(1), stff::vec2(1, 0) }), -1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1) }), stff::constants::half },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0) }), -stff::constants::half },
            { stff::polygon({ stff::vec2(1.00073f, 1.00269f), stff::vec2(1.00073f, 1.00244f), stff::vec2(1.00049f, 1.00244f), stff::vec2(1.00049f, 1.00269f) }), -0.0000000600266503f },
        };
        scaffolding::verify(tests);
    }

    TEST(polygon, contains)
    {
        std::vector<scaffolding::geom::polygon::contains<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0.5), boundary_types::closed, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), boundary_types::closed, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), boundary_types::open, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(-1, 0), boundary_types::closed, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(0.5, 1), boundary_types::closed, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(0.5, 1), boundary_types::open, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(-0.5, 1), boundary_types::closed, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(-0.5, 1), boundary_types::open, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(1), boundary_types::closed, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(1), boundary_types::open, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(0, 1), boundary_types::closed, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(0, 1), boundary_types::open, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 1), stff::vec2(0, 2) }), stff::vec2(1), boundary_types::open, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 1), stff::vec2(0, 2) }), stff::vec2(-1, 1), boundary_types::open, false },
            { stff::polygon({ stff::vec2(0, 2), stff::vec2(2, 0), stff::vec2(4, 2) }), stff::vec2(2, 0), boundary_types::closed, true },
            { stff::polygon({ stff::vec2(0, 2), stff::vec2(2, 0), stff::vec2(4, 2) }), stff::vec2(0), boundary_types::closed, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(0, 4), stff::vec2(2), stff::vec2(4, 4), stff::vec2(4, 0) }), stff::vec2(1), boundary_types::closed, true },
        };
        scaffolding::verify(tests);
    }

    TEST(polygon, distances)
    {
        std::vector<scaffolding::geom::polygon::distances<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), 0 },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0.5, 0), 0 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(1), -1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(3, 1), 1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(3), stff::constants::sqrt_two },
        };
        scaffolding::verify(tests);
    }

} // stf::geom