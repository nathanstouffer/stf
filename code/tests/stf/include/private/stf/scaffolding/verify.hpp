#pragma once

#include <vector>

namespace stf::scaffolding
{

    template<typename test_t>
    void verify(std::vector<test_t> const& tests)
    {
        size_t i = 0;
        for (test_t const& test : tests)
        {
            test.verify(i++);
        }
    }

}