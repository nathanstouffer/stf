#ifndef STF_SCAFFOLDING_ALG_STATISTICS_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_ALG_STATISTICS_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/alg/statistics.hpp>

namespace stf::scaffolding::alg::statistics
{

template <typename T>
struct median
{
    std::vector<T> values;
    T expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::alg::median(values)) << info(i) << "Failed to compute median(values)";
    }
};

} // namespace stf::scaffolding::alg::statistics
#endif
