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

        std::vector<scaffolding::indexed_list::element_t> elements = scaffolding::indexed_list::elements();
        std::vector<std::string> missing = { "five", "six", "seven" };

        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        // verify list size and key presence
        ASSERT_EQ(elements.size(), list.size()) << "Failed size check";
        for (scaffolding::indexed_list::element_t const& element : elements)
        {
            ASSERT_TRUE(list.contains(element.key)) << "Failed to contain expected key '" << element.key << "'";
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

        std::vector<scaffolding::indexed_list::element_t> elements = scaffolding::indexed_list::elements();

        // erase some elements
        list.erase("three");    elements.erase(elements.begin() + 3);
        list.erase("zero");     elements.erase(elements.begin());

        scaffolding::indexed_list::verify(elements, list);
    }

    TEST(indexed_list, find)
    {
        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        for (scaffolding::indexed_list::element_t const& element : scaffolding::indexed_list::elements())
        {
            scaffolding::indexed_list::list_t::iterator found = list.find(element.key);
            ASSERT_NE(list.end(), found) << "Failed to find entry for key '" << element.key << "'";
            ASSERT_EQ(element.key, found->key) << "Failed key comparison for key '" << element.key << "'";
            ASSERT_EQ(element.entry, found->entry) << "Failed entry comparison for key '" << element.key << "'";
        }
    }

    TEST(indexed_list, replace)
    {
        scaffolding::indexed_list::list_t list = scaffolding::indexed_list::construct();

        std::vector<scaffolding::indexed_list::element_t> elements = scaffolding::indexed_list::elements();

        // erase some elements
        list.replace("one", -1);        elements[1].entry = -1;
        list.replace("three", -3);      elements[3].entry = -3;

        scaffolding::indexed_list::verify(elements, list);
    }

} // stf::ds