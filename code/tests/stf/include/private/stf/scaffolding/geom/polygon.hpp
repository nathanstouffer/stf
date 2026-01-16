#ifndef STF_SCAFFOLDING_GEOM_POLYGON_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_GEOM_POLYGON_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/geom/polygon.hpp>

namespace stf::scaffolding::geom::polygon
{

template <typename T>
struct is_convex
{
    stf::geom::polygon<T> polygon;
    bool convex;

    void verify(size_t const i) const
    {
        ASSERT_EQ(convex, polygon.is_convex()) << info(i) << "failed polygon::is_convex";
    }
};

template <typename T>
struct signed_area
{
    stf::geom::polygon<T> polygon;
    T area;

    void verify(size_t const i) const
    {
        ASSERT_NEAR(area, polygon.signed_area(), stf::math::constants<T>::tol_tol)
            << info(i) << "failed polygon::signed_area";
        ASSERT_NEAR(std::abs(area), polygon.area(), stf::math::constants<T>::tol_tol)
            << info(i) << "failed polygon::area";
    }
};

template <typename T>
struct contains
{
    stf::geom::polygon<T> polygon;
    stf::math::vec2<T> query;
    stf::boundary_types boundary_type;
    bool contained;

    void verify(size_t const i) const
    {
        ASSERT_EQ(contained, polygon.contains(query, boundary_type)) << info(i) << "failed polygon::contains";
    }
};

template <typename T>
struct distances
{
    stf::geom::polygon<T> polygon;
    stf::math::vec2<T> query;
    T signed_distance;

    void verify(size_t const i) const
    {
        ASSERT_EQ(signed_distance, polygon.signed_dist(query)) << info(i) << "failed polygon::signed_dist";
        ASSERT_EQ(signed_distance, stf::geom::signed_dist(polygon, query)) << info(i) << "failed geom::signed_dist";
        ASSERT_EQ(signed_distance, stf::geom::signed_dist(query, polygon)) << info(i) << "failed geom::signed_dist";

        T dist = std::max(stf::math::constants<T>::zero, signed_distance);

        ASSERT_EQ(dist, polygon.dist(query)) << info(i) << "failed polygon::dist";
        ASSERT_EQ(dist, stf::geom::dist(polygon, query)) << info(i) << "failed geom::dist";
        ASSERT_EQ(dist, stf::geom::dist(query, polygon)) << info(i) << "failed geom::dist";

        ASSERT_NEAR(dist * dist, polygon.dist_squared(query), stf::math::constants<T>::tol)
            << info(i) << "failed polygon::dist_squared";
        ASSERT_NEAR(dist * dist, stf::geom::dist_squared(polygon, query), stf::math::constants<T>::tol)
            << info(i) << "failed geom::dist_squared";
        ASSERT_NEAR(dist * dist, stf::geom::dist_squared(query, polygon), stf::math::constants<T>::tol)
            << info(i) << "failed geom::dist_squared";
    }
};

} // namespace stf::scaffolding::geom::polygon

#endif