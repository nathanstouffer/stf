#pragma once

#include "constants.h"
#include "math/matrix.h"
#include "math/vector.h"

namespace stf {

    using gpu_float_t = float;

    template<typename T>
    struct instantiate_types
    {

        // vector types
        typedef math::vec<T, 2> vec2;
        typedef math::vec<T, 3> vec3;
        typedef math::vec<T, 4> vec4;

        // matrix types
        typedef math::mtx<T, 2> mtx2;
        typedef math::mtx<T, 3> mtx3;
        typedef math::mtx<T, 4> mtx4;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf