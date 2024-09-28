#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/geom/scaffolding/polygon.hpp"

namespace stf::geom
{
    
    TEST(polygon, is_convex)
    {
        std::vector<scaffolding::polygon::is_convex<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 0), stff::vec2(1) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(0) }), true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(2, -2) }), false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(2, 1), stff::vec2(3, 0), stff::vec2(4, 4) }), false },
        };

        for (scaffolding::polygon::is_convex<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

    TEST(polygon, signed_area)
    {
        std::vector<scaffolding::polygon::signed_area<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), 1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(0, 1), stff::vec2(1), stff::vec2(1, 0) }), -1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1) }), stff::constants::half },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(1, 0) }), -stff::constants::half },
            { stff::polygon({ stff::vec2(1.00073, 1.00269), stff::vec2(1.00073, 1.00244), stff::vec2(1.00049, 1.00244), stff::vec2(1.00049, 1.00269) }), -0.0000000600266503 },
        };

        for (scaffolding::polygon::signed_area<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

    TEST(polygon, contains)
    {
        std::vector<scaffolding::polygon::contains<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0.5), boundary_types::CLOSED, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), boundary_types::CLOSED, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), boundary_types::OPEN, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(-1, 0), boundary_types::CLOSED, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(0.5, 1), boundary_types::CLOSED, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(0.5, 1), boundary_types::OPEN, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(-0.5, 1), boundary_types::CLOSED, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(2, 1), stff::vec2(2), stff::vec2(0, 1) }), stff::vec2(-0.5, 1), boundary_types::OPEN, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(1), boundary_types::CLOSED, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(1), boundary_types::OPEN, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(0, 1), boundary_types::CLOSED, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(1), stff::vec2(2, 0) }), stff::vec2(0, 1), boundary_types::OPEN, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 1), stff::vec2(0, 2) }), stff::vec2(1), boundary_types::OPEN, true },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 1), stff::vec2(0, 2) }), stff::vec2(-1, 1), boundary_types::OPEN, false },
            { stff::polygon({ stff::vec2(0, 2), stff::vec2(2, 0), stff::vec2(4, 2) }), stff::vec2(2, 0), boundary_types::CLOSED, true },
            { stff::polygon({ stff::vec2(0, 2), stff::vec2(2, 0), stff::vec2(4, 2) }), stff::vec2(0), boundary_types::CLOSED, false },
            { stff::polygon({ stff::vec2(0), stff::vec2(0, 4), stff::vec2(2), stff::vec2(4, 4), stff::vec2(4, 0) }), stff::vec2(1), boundary_types::CLOSED, true },
        };

        for (scaffolding::polygon::contains<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

    TEST(polygon, distances)
    {
        std::vector<scaffolding::polygon::distances<float>> tests =
        {
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0), 0 },
            { stff::polygon({ stff::vec2(0), stff::vec2(1, 0), stff::vec2(1), stff::vec2(0, 1) }), stff::vec2(0.5, 0), 0 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(1), -1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(3, 1), 1 },
            { stff::polygon({ stff::vec2(0), stff::vec2(2, 0), stff::vec2(2), stff::vec2(0, 2) }), stff::vec2(3), stff::constants::sqrt_two },
        };

        for (scaffolding::polygon::distances<float> const& test : tests)
        {
            scaffolding::polygon::verify(test);
        }
    }

} // stf::geom