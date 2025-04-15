#pragma once

#include <string>
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

    inline std::string info(size_t const i)
    {
        std::ostringstream msg;
        msg << "(test index: " << i << ") ";
        return msg.str();
    }

}