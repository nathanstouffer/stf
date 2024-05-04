#include <vector>

#include <gtest/gtest.h>

#include <stf/enums.hpp>

namespace stf
{

    TEST(boundary, complement)
    {
        ASSERT_EQ(boundary::CLOSED, complement(boundary::OPEN)) << "failed CLOSED is complement of OPEN";
        ASSERT_EQ(boundary::OPEN, complement(boundary::CLOSED)) << "failed OPEN is complement of CLOSED";
    }

} // stf