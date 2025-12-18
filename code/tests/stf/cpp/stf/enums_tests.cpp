#include <vector>

#include <gtest/gtest.h>

#include <stf/enums.hpp>

namespace stf
{

TEST(boundary_types, complement)
{
    ASSERT_EQ(boundary_types::closed, complement(boundary_types::open))
        << "failed CLOSED is complement of OPEN";
    ASSERT_EQ(boundary_types::open, complement(boundary_types::closed))
        << "failed OPEN is complement of CLOSED";
}

} // namespace stf