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
        typedef math::mat<T, 2> mat2;
        typedef math::mat<T, 3> mat3;
        typedef math::mat<T, 4> mat4;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf