#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/alg/statistics.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::alg
{

TEST(statistics, median)
{
    std::vector<scaffolding::alg::statistics::median<float>> tests = {
        {{0.f}, 0.f},      {{1.f}, 1.f},           {{1.f, 3.f}, 2.f},
        {{3.f, 1.f}, 2.f}, {{6.f, 3.f, 1.f}, 3.f}, {{-5.f, -4.f, -12.f, 4.f, 5.f}, -4.f},
    };
    scaffolding::verify(tests);
}

} // namespace stf::alg