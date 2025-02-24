#pragma once

#include <gtest/gtest.h>

#include <stf/geom/sphere.hpp>

namespace stf::geom::scaffolding::sphere
{

    template<typename T, size_t N>
    struct encloses
    {
        geom::sphere<T, N> const sphere;
        math::vec<T, N> const point;
        bool const enclosed;
    };

    template<typename T, size_t N>
    void verify(encloses<T, N> const& test)
    {
        ASSERT_EQ(test.enclosed, test.sphere.encloses(test.point)) << "failed enclosed test";
    }

} // stf::geom::scaffolding::sphere