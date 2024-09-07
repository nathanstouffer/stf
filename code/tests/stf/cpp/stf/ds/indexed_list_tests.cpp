#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <stf/ds/indexed_list.hpp>

#include "stf/ds/scaffolding/indexed_list.hpp"

namespace stf::ds
{

    TEST(indexed_list, contains)
    {

        std::vector<std::string> present = { "zero", "one", "two", "three", "four" };
        std::vector<std::string> missing = { "five", "six", "seven" };

        // construct list
        indexed_list<std::string, int> list;
        for (std::string const& key : present)
        {
            list.push_back(key, 0);
        }

        // verify list size and key presence
        ASSERT_EQ(present.size(), list.size()) << "Failed size check";
        for (std::string const& key : present)
        {
            ASSERT_TRUE(list.contains(key)) << "Failed to contain expected key: '" << key << "'";
        }

        // verify missing keys
        for (auto const& key : missing)
        {
            ASSERT_FALSE(list.contains(key)) << "Failed to omit missing key: '" << key << "'";
        }
    }

    TEST(indexed_list, find)
    {
        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        for (scaffolding::indexed_list::pair_t const& pair : scaffolding::indexed_list::pairs())
        {
            scaffolding::indexed_list::list_t::iterator found = list.find(pair.key);
            ASSERT_NE(list.end(), found) << "Failed to find entry for key '" << pair.key << "'";
            ASSERT_EQ(pair.key, found->key) << "Failed key comparison for key '" << pair.key << "'";
            ASSERT_EQ(pair.entry, found->entry) << "Failed entry comparison for key '" << pair.key << "'";
        }
    }

} // stf::ds