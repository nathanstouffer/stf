#pragma once

#include "stf/cam/scamera.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace alg {

    template<typename T>
    inline T radians(T const deg)
    {
        T constexpr convert = math::constants<T>::pi / T(180);
        return deg * convert;
    }

    template<typename T>
    inline T degrees(T const rad)
    {
        T constexpr convert = T(180) / math::constants<T>::pi;
        return rad * convert;
    }

    template<typename T>
    inline T canonical_angle(T const theta)
    {
        T canonical = std::fmod(theta, math::constants<T>::tau);
        if (canonical < T(0))
        {
            canonical += math::constants<T>::tau;
        }
        return canonical;
    }

    // of all angles that are equivalent to phi, return the angle that is closest to theta
    template<typename T>
    inline T closest_equiv_angle(T const phi, T const theta)
    {
        T const delta = canonical_angle(phi) - canonical_angle(theta);
        return (delta <= math::constants<T>::pi) ? theta + delta : theta + delta - math::constants<T>::tau;
    }

    template<typename T>
    inline math::vec<T, 2> unit_vector(T const theta)
    {
        return math::vec<T, 2>(std::cos(theta), std::sin(theta));
    }

    template<typename T>
    inline math::vec<T, 3> unit_vector(T const theta, T const phi)
    {
        return cam::scamera<T>::dir(theta, phi);
    }

    template<typename T>
    inline math::vec<T, 3> to_euclidean(T const radius, T const theta, T const phi)
    {
        return radius * unit_vector(theta, phi);
    }

} // alg
} // stf