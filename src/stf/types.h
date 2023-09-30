#pragma once

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

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf