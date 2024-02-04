#pragma once

#include "stf/cam/frustum.hpp"
#include "stf/cam/scamera.hpp"
#include "stf/math/aabb.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/vector.hpp"

using gpu_float_t = float;

namespace stf {

    template<typename T>
    struct instantiate_types
    {

        // constant values
        using constants = math::constants<T>;

        // vector types
        using vec2 = math::vec2<T>;
        using vec3 = math::vec3<T>;
        using vec4 = math::vec4<T>;

        template<size_t N>
        using vec = math::vec<T, N>;

        // matrix types
        using mtx2 = math::mtx2<T>;
        using mtx3 = math::mtx3<T>;
        using mtx4 = math::mtx4<T>;

        // aabb tyes
        using aabb2 = math::aabb2<T>;
        using aabb3 = math::aabb3<T>;

        // camera-related types
        using scamera = cam::scamera<T>;
        using frustum = cam::frustum<T>;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf

// default instantiated types for projects that don't have to worry about precision
using stff = stf::instantiate_types<float>;
using stfd = stf::instantiate_types<double>;
using stfi = stf::instantiate_types<int>;
using stfu = stf::instantiate_types<uint32_t>;