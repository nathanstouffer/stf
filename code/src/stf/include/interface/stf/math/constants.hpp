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
    template<typename T>
    struct constants
    {

        static T constexpr zero = T(0);
        static T constexpr one = T(1);
        static T constexpr half = T(0.5);
        static T constexpr two = T(2);

        static T constexpr sqrt_two = T(1.414213562373095048801688724209);
        static T constexpr sqrt_two_inv = one / sqrt_two;
        
        static T constexpr pi = T(3.141592653589793238462643383279);
        static T constexpr tau = 2 * pi;
        static T constexpr two_pi = tau;
        static T constexpr half_pi = T(0.5) * pi;
        static T constexpr pi_halves = half_pi;
        static T constexpr quarter_pi = T(0.25) * pi;
        static T constexpr pi_fourths = quarter_pi;

        static T constexpr e = T(2.718281828459045235360287471352);

        static T constexpr deg2rad = pi / T(180.0);
        static T constexpr rad2deg = T(180.0) / pi;

        static T constexpr pos_inf = std::numeric_limits<T>::max();
        static T constexpr neg_inf = std::numeric_limits<T>::lowest();

        static T constexpr tol = T(0.00001);
        static T constexpr tol_tol = tol * tol;

    };

} // stf::math