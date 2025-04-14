#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/statistics.hpp>

namespace stf::scaffolding::alg::statistics
{

    template<typename T>
    struct median
    {
        std::vector<T> values;
        T expected;
    };

    template<typename T>
    void verify(median<T> const& test)
    {
        ASSERT_EQ(test.expected, alg::median(test.values)) << "Failed to compute median(values)";
    }

} // stf::scaffolding::alg::statistics