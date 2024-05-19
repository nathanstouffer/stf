#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf::math
{

    template<typename T>
    inline T to_radians(T const deg)
    {
        return deg * math::constants<T>::deg2rad;
    }

    template<typename T>
    inline T to_degrees(T const rad)
    {
        return rad * math::constants<T>::rad2deg;
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

    /**
    * Returns (in radians) the counterclockwise angle from u to v
    */
    template<typename T>
    inline T counterclockwise_angle(vec2<T> const& u, vec2<T> const& v)
    {
        return canonical_angle(std::atan2(cross(u, v), u * v));
    }

    template<typename T>
    inline vec2<T> unit_vector(T const theta)
    {
        return vec2<T>(std::cos(theta), std::sin(theta));
    }

    template<typename T>
    inline vec3<T> unit_vector(T const theta, T const phi)
    {
        return vec3<T>(std::cos(theta) * std::sin(phi), std::sin(theta) * std::sin(phi), std::cos(phi));
    }

    template<typename T>
    inline math::vec3<T> to_euclidean(T const radius, T const theta, T const phi)
    {
        return radius * unit_vector(theta, phi);
    }

} // stf::math