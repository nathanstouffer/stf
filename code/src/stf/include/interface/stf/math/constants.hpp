#pragma once

#include <cmath>

#include <limits>

/**
 * @file constants.hpp
 * @brief A file containing mathematical constants
 */

namespace stf::math
{

/**
 * @brief A templated class that has some common mathematical constants
 * @tparam T Number type (eg float)
 */
template <typename T>
struct constants
{

    /**
     * @brief The constant 0
     */
    static T constexpr zero = T(0);

    /**
     * @brief The constant 1
     */
    static T constexpr one = T(1);

    /**
     * @brief The constant 1/2
     */
    static T constexpr half = T(0.5);

    /**
     * @brief The constant 1/3
     */
    static T constexpr third = T(0.3333333333333333333333333333333);

    /**
     * @brief The constant 1/4
     */
    static T constexpr quarter = T(0.25);

    /**
     * @brief The constant 1/4
     */
    static T constexpr fourth = quarter;

    /**
     * @brief The constant 2
     */
    static T constexpr two = T(2);

    /**
     * @brief The constant sqaure root of 2
     */
    static T constexpr sqrt_two = T(1.414213562373095048801688724209);

    /**
     * @brief The constant 1/sqrt(2)
     */
    static T constexpr sqrt_two_inv = one / sqrt_two;

    /**
     * @brief The constant pi
     */
    static T constexpr pi = T(3.141592653589793238462643383279);

    /**
     * @brief The constant tau (2pi)
     */
    static T constexpr tau = 2 * pi;

    /**
     * @brief The constant 2pi
     */
    static T constexpr two_pi = tau;

    /**
     * @brief The constant pi/2
     */
    static T constexpr half_pi = half * pi;

    /**
     * @brief The constant pi/2
     */
    static T constexpr pi_halves = half_pi;

    /**
     * @brief The constant pi/3
     */
    static T constexpr pi_on_three = third * pi;

    /**
     * @brief The constant pi/3
     */
    static T constexpr pi_thirds = pi_on_three;

    /**
     * @brief The constant pi/4
     */
    static T constexpr quarter_pi = quarter * pi;

    /**
     * @brief The constant pi/4
     */
    static T constexpr pi_fourths = quarter_pi;

    /**
     * @brief The constant e
     */
    static T constexpr e = T(2.718281828459045235360287471352);

    /**
     * @brief The constant that converts degrees to radians
     */
    static T constexpr deg2rad = pi / T(180.0);

    /**
     * @brief The constant that converts radians to degrees
     */
    static T constexpr rad2deg = T(180.0) / pi;

    /**
     * @brief A value greater than all other values of type @p T
     */
    static T constexpr pos_inf = std::numeric_limits<T>::max();

    /**
     * @brief A value less than all other values of type @p T
     */
    static T constexpr neg_inf = std::numeric_limits<T>::lowest();

    /**
     * @brief A constant error tolerance
     */
    static T constexpr tol = T(0.00001);

    /**
     * @brief A smaller constant error tolerance
     */
    static T constexpr tol_tol = tol * tol;
};

} // namespace stf::math