#pragma once

#include <cstdint>

#include "stf/cam/frustum.hpp"
#include "stf/cam/scamera.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/holygon.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/geom/polyline.hpp"
#include "stf/geom/ray.hpp"
#include "stf/geom/segment.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/cinterval.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/interval.hpp"
#include "stf/math/vector.hpp"

/**
 * @file stf.hpp
 * @brief A file containing type instantiations to reduce verbosity for users of stf
 */

using gpu_float_t = float;

namespace stf
{

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

        // interval types
        using cinterval = math::cinterval<T>;
        using interval = math::interval<T>;

        // aabb tyes
        using aabb2 = geom::aabb2<T>;
        using aabb3 = geom::aabb3<T>;

        // segment types
        using segment2 = geom::segment2<T>;
        using segment3 = geom::segment3<T>;

        // ray types
        using ray2 = geom::ray2<T>;
        using ray3 = geom::ray3<T>;

        // planar geometry types
        using polyline2 = geom::polyline2<T>;
        using polygon = geom::polygon<T>;
        using holygon = geom::holygon<T>;

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