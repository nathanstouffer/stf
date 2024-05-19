#pragma once

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::spatial::scaffolding::interval_tree
{

    template<typename T>
    struct find
    {

        spatial::interval_tree<T, std::string> tree;
        T query;
        std::vector<typename spatial::interval_tree<T, std::string>::entry_t> expected; // not necessarily in order

    };

    template<typename T>
    void verify(find<T> const& test)
    {

        std::vector<bool> indicators(test.expected.size(), false);
        size_t count = 0;
        for (typename spatial::interval_tree<T, std::string>::entry_t const& entry : test.tree.find(test.query))
        {
            ++count;
            
            auto found = std::find(test.expected.begin(), test.expected.end(), entry);
            ASSERT_NE(found, test.expected.end()) << "interval_tree::find returned unexpected value: " + found->value;
            
            // update the indicators
            size_t i = found - test.expected.begin();
            indicators[i] = true;
        }

        // check that all entries were found
        for (size_t i = 0; i < indicators.size(); ++i)
        {
            ASSERT_TRUE(indicators[i]) << "Failed to find value: " + test.expected[i].value;
        }
        // check that the correct number of entries was found
        ASSERT_EQ(test.expected.size(), count) << "interval_tree::find returned an incorrect number of values";
    }

} // stf::spatial::scaffolding::interval_tree