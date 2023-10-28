#pragma once

#include <cmath>

#include "stf/cam/scamera.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace alg {

    template<typename T>
    inline math::vec2<T> rotate(math::vec2<T> const& val, T const theta)
    {
        return math::rotate_plane<T>(theta) * val;
    }

    template<typename T>
    inline math::vec2<T> orbit(math::vec3<T> const& val, math::vec2<T> const& focus, T const theta)
    {
        return rotate(val - focus, theta) + focus;
    }

    // NOTE: we assume axis is a unit vector
    // NOTE: rotates about the origin
    template<typename T>
    inline math::vec3<T> rotate(math::vec3<T> const& val, math::vec3<T> const& axis, T const theta)
    {
        return axis * (axis * val) + std::cos(theta) * cross(cross(axis, val), axis) + std::sin(theta) * cross(axis, val);
    }

    // NOTE: we assume angles are from the perspective of the focus point and that right is a unit vector
    template<typename T>
    inline math::vec3<T> orbit(math::vec3<T> const& val, math::vec3<T> const& focus, math::vec3<T> const& right, T const delta_phi, T const delta_theta)
    {
        math::vec3<T> relative = val - focus;
        relative = rotate(relative, right, delta_phi);
        relative = rotate(relative, math::vec3<T>(0, 0, 1), delta_theta);
        return relative + focus;
    }

    template<typename T>
    inline cam::scamera<T> orbit(cam::scamera<T> const& camera, math::vec3<T>);

} // alg
} // stf