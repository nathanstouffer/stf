#include <vector>

#include <gtest/gtest.h>

#include <stf/spatial/interval_tree.hpp>

#include "stf/spatial/scaffolding/interval_tree.hpp"

namespace stf::spatial
{

    TEST(interval_tree, find)
    {
        using tree_t = typename interval_tree<float, std::string>;
        using entry_t = typename tree_t::entry_t;
        
        // TODO make this an initializer list once interval_tree is copyable
        std::vector<scaffolding::interval_tree::find<float>> tests;
        tests.push_back({ tree_t({}), 0, {} });
        tests.push_back({ tree_t({}), 5, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first") }), 0, { entry_t(stff::interval(0, 1), "first") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first") }), 0.5, { entry_t(stff::interval(0, 1), "first") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first") }), 1, { entry_t(stff::interval(0, 1), "first") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first") }), -1, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first") }), 2, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") }), 0, { entry_t(stff::interval(0, 1), "first") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") }), 2, { entry_t(stff::interval(1, 2), "second") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") }), 1, { entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") }), -1, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(1, 2), "second") }), 10, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(3, 4), "second") }), 2, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second"), entry_t(stff::interval(-2, 2), "third") }), 0, { entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second"), entry_t(stff::interval(-2, 2), "third") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second"), entry_t(stff::interval(-2, 2), "third") }), 3, { entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second"), entry_t(stff::interval(-2, 2), "third") }), -3, { entry_t(stff::interval(-5, 5), "first"), entry_t(stff::interval(-4, 4), "second") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(-1, 1), "first"), entry_t(stff::interval(-1, 1), "second"), entry_t(stff::interval(-1, 1), "third") }), 0, { entry_t(stff::interval(-1, 1), "first"), entry_t(stff::interval(-1, 1), "second"), entry_t(stff::interval(-1, 1), "third") } });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(2, 3), "second"), entry_t(stff::interval(4, 5), "third"), entry_t(stff::interval(6, 7), "fourth") }), 3.5, {} });
        tests.push_back({ tree_t({ entry_t(stff::interval(0, 1), "first"), entry_t(stff::interval(2, 3), "second"), entry_t(stff::interval(4, 5), "third"), entry_t(stff::interval(6, 7), "fourth") }), 2, { entry_t(stff::interval(2, 3), "second") } });

        for (scaffolding::interval_tree::find<float> const& test : tests) { scaffolding::interval_tree::verify(test); }
    }

} // stf::spatial