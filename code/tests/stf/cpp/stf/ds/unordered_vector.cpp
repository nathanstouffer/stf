#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <stf/ds/unordered_vector.hpp>

#include "stf/scaffolding/ds/unordered_vector.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::ds
{

TEST(unordered_vector, contains)
{

    std::vector<scaffolding::ds::unordered_vector::element_t> elements = scaffolding::ds::unordered_vector::elements();
    std::vector<std::string> missing = {"five", "six", "seven"};

    scaffolding::ds::unordered_vector::list_t list = scaffolding::ds::unordered_vector::construct();

    // verify list size and key presence
    ASSERT_EQ(elements.size(), list.size()) << "Failed size check";
    for (scaffolding::ds::unordered_vector::element_t const& element : elements)
    {
        ASSERT_TRUE(list.contains(element.key)) << "Failed to contain expected key '" << element.key << "'";
    }

    // verify missing keys
    for (auto const& key : missing)
    {
        ASSERT_FALSE(list.contains(key)) << "Failed to omit missing key '" << key << "'";
    }
}

} // namespace stf::ds