#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/cam/scamera.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::cam
{

TEST(scamera, direction_vectors)
{
    float constexpr half_pi = stff::constants::half_pi;
    float constexpr pi = stff::constants::pi;

    std::vector<scaffolding::cam::scamera::direction_vectors<float>> tests = {
        // camera                               look                        // up // right
        {stff::scamera(half_pi, pi), stff::vec3(0, 0, -1), stff::vec3(0, 1, 0),
         stff::vec3(1, 0, 0)},
        {stff::scamera(pi, pi), stff::vec3(0, 0, -1), stff::vec3(-1, 0, 0), stff::vec3(0, 1, 0)},
        {stff::scamera(0, pi), stff::vec3(0, 0, -1), stff::vec3(1, 0, 0), stff::vec3(0, -1, 0)},
        {stff::scamera(half_pi, half_pi), stff::vec3(0, 1, 0), stff::vec3(0, 0, 1),
         stff::vec3(1, 0, 0)},
        {stff::scamera(pi, half_pi), stff::vec3(-1, 0, 0), stff::vec3(0, 0, 1),
         stff::vec3(0, 1, 0)},
        {stff::scamera(0, half_pi), stff::vec3(1, 0, 0), stff::vec3(0, 0, 1), stff::vec3(0, -1, 0)},
    };
    scaffolding::verify(tests);
}

TEST(scamera, lerp)
{
    float constexpr quarter_pi = stff::constants::quarter_pi;
    float constexpr half_pi = stff::constants::half_pi;
    float constexpr pi = stff::constants::pi;

    std::vector<scaffolding::cam::scamera::lerp<float>> tests = {
        // lhs                                       rhs                                          //
        // t   // expected same endpoints
        {stff::scamera(half_pi, pi), stff::scamera(half_pi, pi), 0, stff::scamera(half_pi, pi)},
        {stff::scamera(half_pi, pi), stff::scamera(half_pi, pi), 0.25, stff::scamera(half_pi, pi)},
        {stff::scamera(half_pi, pi), stff::scamera(half_pi, pi), 0.5, stff::scamera(half_pi, pi)},
        {stff::scamera(half_pi, pi), stff::scamera(half_pi, pi), 0.75, stff::scamera(half_pi, pi)},
        {stff::scamera(half_pi, pi), stff::scamera(half_pi, pi), 1, stff::scamera(half_pi, pi)},
        // different endpoints
        {stff::scamera(stff::vec3(0), half_pi, pi), stff::scamera(stff::vec3(1), 0, half_pi), 0,
         stff::scamera(stff::vec3(0), half_pi, pi)},
        {stff::scamera(stff::vec3(0), half_pi, pi), stff::scamera(stff::vec3(1), 0, half_pi), 0.5,
         stff::scamera(stff::vec3(0.5), quarter_pi, 3.f * quarter_pi)},
        {stff::scamera(stff::vec3(0), half_pi, pi), stff::scamera(stff::vec3(1), 0, half_pi), 1,
         stff::scamera(stff::vec3(1), 0, half_pi)},
    };
    scaffolding::verify(tests);
}

TEST(scamera, orbit)
{
    float constexpr half_pi = stff::constants::half_pi;
    float constexpr pi = stff::constants::pi;

    std::vector<scaffolding::cam::scamera::orbit<float>> tests = {
        // initial                                          focus           delta phi delta theta
        // expected
        {stff::scamera(stff::vec3(0, 0, 10), half_pi, pi), stff::vec3(0), stff::constants::zero,
         stff::constants::zero, stff::scamera(stff::vec3(0, 0, 10), half_pi, pi)},
        {stff::scamera(stff::vec3(0, 0, 10), half_pi, pi), stff::vec3(0), -stff::constants::half_pi,
         stff::constants::pi, stff::scamera(stff::vec3(0, 10, 0), pi + half_pi, half_pi)},
    };
    scaffolding::verify(tests);
}

} // namespace stf::cam