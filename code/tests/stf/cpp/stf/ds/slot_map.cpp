#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <stf/ds/slot_map.hpp>

#include "stf/scaffolding/verify.hpp"

namespace stf::ds
{

TEST(slot_map, simple_insert)
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
        map.insert(test.value);
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
        map.insert(test.value);
    };

    map.erase(0);
    map.erase(2);

    ASSERT_EQ(3, map.size()) << "Failed size check for map";
    ASSERT_EQ(map.end(), map.find(0)) << "Failed to erase key 0";
    ASSERT_EQ(map.end(), map.find(2)) << "Failed to erase key 2";

    {
        auto found = map.find(1);
        ASSERT_NE(map.end(), found) << "Erroneously erased key 1";
        ASSERT_EQ("one", *found) << "Incorrect value at key 1";
    }

    {
        auto found = map.find(3);
        ASSERT_NE(map.end(), found) << "Erroneously erased key 3";
        ASSERT_EQ("three", *found) << "Incorrect value at key 3";
    }

    {
        auto found = map.find(4);
        ASSERT_NE(map.end(), found) << "Erroneously erased key 4";
        ASSERT_EQ("four", *found) << "Incorrect value at key 4";
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
        map.insert(test.value);
    };

    map.erase(4);

    ASSERT_EQ(4, map.size()) << "Failed size check for map";
    {
        auto found = map.find(4);
        ASSERT_EQ(map.end(), found) << "Failed to erase key 4";
    }
}

} // namespace stf::ds