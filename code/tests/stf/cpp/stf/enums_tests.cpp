#include <vector>

#include <gtest/gtest.h>

#include <stf/enums.hpp>

namespace stf
{

    TEST(boundary_types, complement)
    {
        ASSERT_EQ(boundary_types::CLOSED, complement(boundary_types::OPEN)) << "failed CLOSED is complement of OPEN";
        ASSERT_EQ(boundary_types::OPEN, complement(boundary_types::CLOSED)) << "failed OPEN is complement of CLOSED";
    }

} // stf