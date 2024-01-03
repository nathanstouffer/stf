#include <vector>

#include <gtest/gtest.h>

#include <stf/types.hpp>

#include "stf/cam/scaffolding/scamera.hpp"

namespace stf::cam
{

    TEST(scamera, direction_vectors)
    {
        float constexpr half_pi = stff::constants::half_pi;
        float constexpr pi = stff::constants::pi;

        std::vector<scaffolding::scamera::direction_vectors<float>> tests =
        {
            // camera                               look                        // up                       // right
            { stff::scamera(half_pi, pi),           stff::vec3(0, 0, -1),       stff::vec3(0, 1, 0),        stff::vec3(1, 0, 0) },
            { stff::scamera(pi, pi),                stff::vec3(0, 0, -1),       stff::vec3(-1, 0, 0),       stff::vec3(0, 1, 0) },
            { stff::scamera(0, pi),                 stff::vec3(0, 0, -1),       stff::vec3(1, 0, 0),        stff::vec3(0, -1, 0) },
            { stff::scamera(half_pi, half_pi),      stff::vec3(0, 1, 0),        stff::vec3(0, 0, 1),        stff::vec3(1, 0, 0) },
            { stff::scamera(pi, half_pi),           stff::vec3(-1, 0, 0),       stff::vec3(0, 0, 1),        stff::vec3(0, 1, 0) },
            { stff::scamera(0, half_pi),            stff::vec3(1, 0, 0),        stff::vec3(0, 0, 1),        stff::vec3(0, -1, 0) },
        };

        for (scaffolding::scamera::direction_vectors<float> const& test : tests) { scaffolding::scamera::verify(test); }
    }

} // stf::cam