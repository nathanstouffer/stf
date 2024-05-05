#pragma once

#include <gtest/gtest.h>

#include <stf/stf.hpp>
#include <stf/cam/scamera.hpp>

namespace stf::spatial::scaffolding::interval_tree
{

    template<typename T>
    struct something
    {
    };

    template<typename T>
    void verify(something<T> const& test)
    {
        //ASSERT_EQ(test.look, test.camera.look()) << "Failed to compute look vector";
    }

} // stf::spatial::scaffolding::interval_tree