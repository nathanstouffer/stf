#pragma once

#include <cmath>

#include "stf/cam/scamera.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace alg {

    template<typename T>
    inline math::vec<T, 2> rotate(math::vec<T, 2> const& val, T const theta)
    {
        return math::rotate_plane<T>(theta) * val;
    }

    template<typename T>
    inline math::vec<T, 2> orbit(math::vec<T, 3> const& val, math::vec<T, 2> const& focus, T const theta)
    {
        return rotate(val - focus, theta) + focus;
    }

    // NOTE: we assume axis is a unit vector
    // NOTE: rotates about the origin
    template<typename T>
    inline math::vec<T, 3> rotate(math::vec<T, 3> const& val, math::vec<T, 3> const& axis, T const theta)
    {
        return axis * (axis * val) + std::cos(theta) * cross(cross(axis, val), axis) + std::sin(theta) * cross(axis, val);
    }

    // NOTE: we assume angles are from the perspective of the focus point and that right is a unit vector
    template<typename T>
    inline math::vec<T, 3> orbit(math::vec<T, 3> const& val, math::vec<T, 3> const& focus, math::vec<T, 3> const& right, T const delta_phi, T const delta_theta)
    {
        math::vec<T, 3> relative = val - focus;
        relative = rotate(relative, right, delta_phi);
        relative = rotate(relative, math::vec<T, 3>(0, 0, 1), delta_theta);
        return relative + focus;
    }

} // alg
} // stf