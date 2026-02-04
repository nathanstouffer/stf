#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <stf/ds/slot_map.hpp>

#include "stf/scaffolding/ds/slot_map.hpp"
#include "stf/scaffolding/verify.hpp"

// TODO (stouff) perhaps extract scaffolding to header file?
namespace stf::ds
{

TEST(slot_map, simple_push)
{
    slot_map<std::string> map;

    struct test_t
    {
        std::string value;
        size_t id;
    };

    std::vector<test_t> tests = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    };

    for (auto& test : tests)
    {
        map.push(test.value);
    };

    for (auto& test : tests)
    {
        ASSERT_EQ(test.value, map[test.id]) << "Failed to push item";
    }
}

} // namespace stf::ds