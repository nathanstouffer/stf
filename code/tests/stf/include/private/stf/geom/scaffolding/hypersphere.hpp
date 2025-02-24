#pragma once

#include <gtest/gtest.h>

#include <stf/geom/hypersphere.hpp>

namespace stf::geom::scaffolding::hypersphere
{

    template<typename T, size_t N>
    struct encloses
    {
        geom::hypersphere<T, N> const hypersphere;
        math::vec<T, N> const point;
        bool const enclosed;
    };

    template<typename T, size_t N>
    void verify(encloses<T, N> const& test)
    {
        ASSERT_EQ(test.enclosed, test.hypersphere.encloses(test.point)) << "failed enclosed test";
    }

} // stf::geom::scaffolding::sphere