#pragma once

#include "stf/cam/scamera.hpp"
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
        using vec2 = math::vec<T, 2>;
        using vec3 = math::vec<T, 3>;
        using vec4 = math::vec<T, 4>;

        template<size_t N>
        using vec = math::vec<T, N>;

        // matrix types
        using mtx2 = math::mtx<T, 2>;
        using mtx3 = math::mtx<T, 3>;
        using mtx4 = math::mtx<T, 4>;

        using scamera = cam::scamera<T>;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf

// default instantiated types for projects that don't have to worry about precision
using stff = stf::instantiate_types<float>;
using stfd = stf::instantiate_types<double>;
using stfi = stf::instantiate_types<int>;
using stfu = stf::instantiate_types<uint32_t>;