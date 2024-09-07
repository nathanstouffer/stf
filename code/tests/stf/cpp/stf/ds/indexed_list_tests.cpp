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

        std::vector<scaffolding::indexed_list::pair_t> pairs = scaffolding::indexed_list::pairs();
        std::vector<std::string> missing = { "five", "six", "seven" };

        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        // verify list size and key presence
        ASSERT_EQ(pairs.size(), list.size()) << "Failed size check";
        for (scaffolding::indexed_list::pair_t const& pair : pairs)
        {
            ASSERT_TRUE(list.contains(pair.key)) << "Failed to contain expected key '" << pair.key << "'";
        }

        // verify missing keys
        for (auto const& key : missing)
        {
            ASSERT_FALSE(list.contains(key)) << "Failed to omit missing key '" << key << "'";
        }
    }

    TEST(indexed_list, erase)
    {
        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        std::vector<scaffolding::indexed_list::pair_t> pairs = scaffolding::indexed_list::pairs();

        // erase some pairs
        list.erase("three");    pairs.erase(pairs.begin() + 3);
        list.erase("zero");     pairs.erase(pairs.begin());

        scaffolding::indexed_list::verify(pairs, list);
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

    TEST(indexed_list, replace)
    {
        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        std::vector<scaffolding::indexed_list::pair_t> pairs = scaffolding::indexed_list::pairs();

        // erase some pairs
        list.replace("one", -1);        pairs[1].entry = -1;
        list.replace("three", -3);      pairs[3].entry = -3;

        scaffolding::indexed_list::verify(pairs, list);
    }

} // stf::ds