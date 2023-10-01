#pragma once

// TODO (stouff) set this up with absolute includes
#include "../math/vector.h"

namespace stf {
namespace alg {

    template<typename T>
    inline T canonical_angle(T const theta)
    {
        T canonical = std::fmod(theta, TWO_PI);
        if (canonical < T(0))
        {
            canonical += TWO_PI;
        }
        return canonical;
    }

    // of all angles that are equivalent to phi, return the angle that is closest to theta
    template<typename T>
    inline T closest_equiv_angle(T const theta, T const phi)
    {
        if (std::abs(theta - phi) <= PI)
        {
            return phi;
        }
        else
        {
            T tau = TWO_PI;
            return (theta < phi) ? closest_equiv_angle(theta, phi - tau) : closest_equiv_angle(theta, phi + tau);
        }
    }

    template<typename T>
    inline T deg_to_rad(T const degrees)
    {
        T constexpr convert = PI / T(180);
        return degrees * convert;
    }

    template<typename T>
    inline T rad_to_deg(T const radians)
    {
        T constexpr convert = T(180) / PI;
        return radians * convert;
    }

    template<typename T>
    inline math::vec<T, 2> direction(T const theta)
    {
        return math::vec<T, 2>(std::cos(theta), std::sin(theta));
    }

} // alg
} // stf