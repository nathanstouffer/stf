#pragma once

#include "constants.h"
#include "math/matrix.h"
#include "math/vector.h"

using gpu_float_t = float;

namespace stf {

    template<typename T>
    struct instantiate_types
    {

        // vector types
        using vec2 = math::vec<T, 2>;
        using vec3 = math::vec<T, 3>;
        using vec4 = math::vec<T, 4>;

        // matrix types
        using mtx2 = math::mtx<T, 2>;
        using mtx3 = math::mtx<T, 3>;
        using mtx4 = math::mtx<T, 4>;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf

// default instantiated types for projects that don't have to worry about precision
using stff = stf::instantiate_types<float>;
using stfd = stf::instantiate_types<double>;