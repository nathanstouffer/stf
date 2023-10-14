#pragma once

// TODO (stouff) set this up with absolute includes
#include "../constants.h"
#include "../math/vector.h"

namespace stf {
namespace alg {

    template<typename T>
    inline T canonical_angle(T const theta)
    {
        T canonical = std::fmod(theta, constants<T>::tau);
        if (canonical < T(0))
        {
            canonical += constants<T>::tau;
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
            return (constants<T>::tau < phi) ? closest_equiv_angle(theta, phi - tau) : closest_equiv_angle(theta, phi + tau);
        }
    }

    template<typename T>
    inline T rad(T const degrees)
    {
        T constexpr convert = constants<T>::pi / T(180);
        return degrees * convert;
    }

    template<typename T>
    inline T deg(T const radians)
    {
        T constexpr convert = T(180) / constants<T>::pi;
        return radians * convert;
    }

    template<typename T>
    inline math::vec<T, 2> direction(T const theta)
    {
        return math::vec<T, 2>(std::cos(theta), std::sin(theta));
    }

} // alg
} // stf