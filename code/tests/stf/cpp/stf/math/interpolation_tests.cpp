#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/math/interpolation.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::math
{
TEST(interpolation, lerp)
{
    std::vector<scaffolding::math::interpolation::lerp<float>> tests = {
        {0, 1, -1, -1},      {0, 1, 0, 0},      {0, 1, 0.25, 0.25}, {0, 1, 0.5, 0.5},
        {0, 1, 0.75, 0.75},  {0, 1, 1, 1},      {0, 1, 2, 2},       {0, 40, -1, -40},
        {0, 40, 0, 0},       {0, 40, 0.25, 10}, {0, 40, 0.5, 20},   {0, 40, 0.75, 30},
        {0, 40, 1, 40},      {0, 40, 2, 80},    {-10, 10, -1, -30}, {-10, 10, 0, -10},
        {-10, 10, 0.25, -5}, {-10, 10, 0.5, 0}, {-10, 10, 0.75, 5}, {-10, 10, 1, 10},
        {-10, 10, 2, 30},
    };
    scaffolding::verify(tests);
}

TEST(interpolation, lerp_inv)
{
    std::vector<scaffolding::math::interpolation::lerp_inv<float>> tests = {
        {0, 1, -1, -1},      {0, 1, 0, 0},      {0, 1, 0.25, 0.25}, {0, 1, 0.5, 0.5},
        {0, 1, 0.75, 0.75},  {0, 1, 1, 1},      {0, 1, 2, 2},       {0, 40, -40, -1},
        {0, 40, 0, 0},       {0, 40, 10, 0.25}, {0, 40, 20, 0.5},   {0, 40, 30, 0.75},
        {0, 40, 40, 1},      {0, 40, 80, 2},    {-10, 10, -30, -1}, {-10, 10, -10, 0},
        {-10, 10, -5, 0.25}, {-10, 10, 0, 0.5}, {-10, 10, 5, 0.75}, {-10, 10, 10, 1},
        {-10, 10, 30, 2},
    };
    scaffolding::verify(tests);
}

TEST(interpolation, lerpstep)
{
    std::vector<scaffolding::math::interpolation::lerpstep<float>> tests = {
        {0, 1, -1, 0},       {0, 1, 0, 0},      {0, 1, 0.25, 0.25}, {0, 1, 0.5, 0.5},
        {0, 1, 0.75, 0.75},  {0, 1, 1, 1},      {0, 1, 2, 1},       {0, 40, -1, 0},
        {0, 40, 0, 0},       {0, 40, 0.25, 10}, {0, 40, 0.5, 20},   {0, 40, 0.75, 30},
        {0, 40, 1, 40},      {0, 40, 2, 40},    {-10, 10, -1, -10}, {-10, 10, 0, -10},
        {-10, 10, 0.25, -5}, {-10, 10, 0.5, 0}, {-10, 10, 0.75, 5}, {-10, 10, 1, 10},
        {-10, 10, 2, 10},
    };
    scaffolding::verify(tests);
}

} // namespace stf::math