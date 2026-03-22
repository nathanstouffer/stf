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
        size_t key;
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
        ASSERT_EQ(test.value, map[test.key]) << "Failed to push item";
    }
}

TEST(slot_map, erase)
{
    slot_map<std::string> map;

    struct test_t
    {
        std::string value;
        size_t key;
    };

    std::vector<test_t> tests = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    };

    for (auto& test : tests)
    {
        map.push(test.value);
    };

    map.erase(0);
    map.erase(2);

    ASSERT_EQ(3, map.size()) << "Failed size check for map";
    ASSERT_EQ(map.end(), map.find(0)) << "Failed to erase id 0";
    ASSERT_EQ(map.end(), map.find(2)) << "Failed to erase id 2";

    {
        auto found = map.find(1);
        ASSERT_EQ(map.end(), found) << "Erroneously erased id 1";
        // TODO (stouff) add assertion bound found entry
    }
}

TEST(slot_map, erase_end)
{
    slot_map<std::string> map;

    struct test_t
    {
        std::string value;
        size_t key;
    };

    std::vector<test_t> tests = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    };

    for (auto& test : tests)
    {
        map.push(test.value);
    };

    map.erase(4);

    ASSERT_EQ(4, map.size()) << "Failed size check for map";
}

} // namespace stf::ds