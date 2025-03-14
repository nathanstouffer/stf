#pragma once

#include <gtest/gtest.h>

#include <stf/geom/polygon.hpp>

namespace stf::geom::scaffolding::polygon
{

    template<typename T>
    struct is_convex
    {
        geom::polygon<T> polygon;
        bool convex;
    };

    template<typename T>
    void verify(is_convex<T> const& test)
    {
        ASSERT_EQ(test.convex, test.polygon.is_convex()) << "failed polygon::is_convex";
    }

    template<typename T>
    struct signed_area
    {
        geom::polygon<T> polygon;
        T area;
    };

    template<typename T>
    void verify(signed_area<T> const& test)
    {
        ASSERT_EQ(test.area, test.polygon.signed_area()) << "failed polygon::signed_area";
        ASSERT_EQ(std::abs(test.area), test.polygon.area()) << "failed polygon::area";
    }

    template<typename T>
    struct contains
    {
        geom::polygon<T> polygon;
        math::vec2<T> query;
        boundary_types boundary_type;
        bool contained;
    };

    template<typename T>
    void verify(contains<T> const& test)
    {
        ASSERT_EQ(test.contained, test.polygon.contains(test.query, test.boundary_type)) << "failed polygon::contains";
    }

    template<typename T>
    struct distances
    {
        geom::polygon<T> polygon;
        math::vec2<T> query;
        T signed_distance;
    };

    template<typename T>
    void verify(distances<T> const& test)
    {
        ASSERT_EQ(test.signed_distance, test.polygon.signed_dist(test.query)) << "failed polygon::signed_dist";
        ASSERT_EQ(test.signed_distance, geom::signed_dist(test.polygon, test.query)) << "failed geom::signed_dist";
        ASSERT_EQ(test.signed_distance, geom::signed_dist(test.query, test.polygon)) << "failed geom::signed_dist";
        
        T dist = std::max(math::constants<T>::zero, test.signed_distance);

        ASSERT_EQ(dist, test.polygon.dist(test.query)) << "failed polygon::dist";
        ASSERT_EQ(dist, geom::dist(test.polygon, test.query)) << "failed geom::dist";
        ASSERT_EQ(dist, geom::dist(test.query, test.polygon)) << "failed geom::dist";
        
        ASSERT_NEAR(dist * dist, test.polygon.dist_squared(test.query), math::constants<T>::tol) << "failed polygon::dist_squared";
        ASSERT_NEAR(dist * dist, geom::dist_squared(test.polygon, test.query), math::constants<T>::tol) << "failed geom::dist_squared";
        ASSERT_NEAR(dist * dist, geom::dist_squared(test.query, test.polygon), math::constants<T>::tol) << "failed geom::dist_squared";
    }

}