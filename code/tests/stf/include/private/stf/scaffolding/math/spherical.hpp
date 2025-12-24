#ifndef STF_SCAFFOLDING_MATH_SPHERICAL_HPP_HEADER_GUARD
#define STF_SCAFFOLDING_MATH_SPHERICAL_HPP_HEADER_GUARD

#include <gtest/gtest.h>

#include <stf/math/spherical.hpp>
#include <stf/stf.hpp>

namespace stf::scaffolding::math::spherical
{

template <typename T>
struct conversion
{
    T radians;
    T degrees;

    void verify(size_t const i) const
    {
        ASSERT_FLOAT_EQ(degrees, stf::math::to_degrees(radians)) << info(i) << "Failed to convert radians to degrees";
        ASSERT_FLOAT_EQ(radians, stf::math::to_radians(degrees)) << info(i) << "Failed to convert degrees to radians";
    }
};

template <typename T>
struct canonical_angle
{
    T radians;
    T expected;

    void verify(size_t const i) const
    {
        ASSERT_FLOAT_EQ(expected, stf::math::canonical_angle(radians))
            << info(i) << "Failed to compute canonical angle";
    }
};

template <typename T>
struct closest_equiv_angle
{
    T phi;
    T theta;
    T expected;

    void verify(size_t const i) const
    {
        // NOTE: unfortunately, we had to relax floating point equality on this on a bit
        ASSERT_NEAR(expected, stf::math::closest_equiv_angle(phi, theta), stf::math::constants<T>::tol)
            << info(i) << "Failed to compute closest equivalent angle";
    }
};

template <typename T>
struct counterclockwise_angle
{
    stf::math::vec2<T> u;
    stf::math::vec2<T> v;
    T theta;

    void verify(size_t const i) const
    {
        ASSERT_FLOAT_EQ(theta, stf::math::counterclockwise_angle(u, v))
            << info(i) << "Failed to compute counterclockwise angle";
    }
};

template <typename T>
struct unit_vec2
{
    T theta;
    stf::math::vec<T, 2> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::unit_vector(theta)) << info(i) << "Failed to compute unit vector";
    }
};

template <typename T>
struct to_euclidean
{
    T radius;
    T theta;
    T phi;
    stf::math::vec<T, 3> expected;

    void verify(size_t const i) const
    {
        ASSERT_EQ(expected, stf::math::to_euclidean(radius, theta, phi))
            << info(i) << "Failed to compute euclidean coordinates";
    }
};

} // namespace stf::scaffolding::math::spherical
#endif
