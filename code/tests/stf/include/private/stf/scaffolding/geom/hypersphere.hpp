#ifndef STF_SCAFFOLDING_GEOM_HYPERSPHERE_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_GEOM_HYPERSPHERE_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/geom/hypersphere.hpp>

namespace stf::scaffolding::geom::hypersphere
{

template <typename T, size_t N>
struct encloses
{
    stf::geom::hypersphere<T, N> const hypersphere;
    stf::math::vec<T, N> const point;
    bool const enclosed;

    void verify(size_t const i) const
    {
        ASSERT_EQ(enclosed, hypersphere.encloses(point)) << info(i) << "failed enclosed test";
    }
};

} // namespace stf::scaffolding::geom::hypersphere
#endif
