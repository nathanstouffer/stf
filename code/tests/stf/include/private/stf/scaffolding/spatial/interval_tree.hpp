#pragma once

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::scaffolding::spatial::interval_tree
{

    template<typename T>
    struct find
    {

        stf::spatial::interval_tree<T, std::string> tree;
        T query;
        std::vector<typename stf::spatial::interval_tree<T, std::string>::entry_t> expected; // not necessarily in order

        void verify(size_t const index) const
        {
            std::vector<bool> indicators(expected.size(), false);
            size_t count = 0;
            for (typename stf::spatial::interval_tree<T, std::string>::entry_t const& entry : tree.find(query))
            {
                ++count;
            
                auto found = std::find(expected.begin(), expected.end(), entry);
                ASSERT_NE(found, expected.end()) << info(index) << "interval_tree::find returned unexpected value: " + found->value;
            
                // update the indicators
                size_t i = found - expected.begin();
                indicators[i] = true;
            }

            // check that all entries were found
            for (size_t i = 0; i < indicators.size(); ++i)
            {
                ASSERT_TRUE(indicators[i]) << info(index) << "Failed to find value: " + expected[i].value;
            }
            // check that the correct number of entries was found
            ASSERT_EQ(expected.size(), count) << info(index) << "interval_tree::find returned an incorrect number of values";
        }
    };

} // stf::scaffolding::spatial::interval_tree