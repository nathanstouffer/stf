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

    /**
     * @brief Struct that defines type aliases for various templated types
     * @tparam T Number type (eg float)
     */
    template<typename T>
    struct instantiate_types
    {

        /**
         * @brief Type alias for constants
         */
        using constants = math::constants<T>;

        /**
         * @brief Type alias for vec2
         */
        using vec2 = math::vec2<T>;

        /**
         * @brief Type alias for vec3
         */
        using vec3 = math::vec3<T>;

        /**
         * @brief Type alias for vec4
         */
        using vec4 = math::vec4<T>;

        /**
         * @brief Type alias for n-dimensional vector
         * @tparam N Dimension
         */
        template<size_t N>
        using vec = math::vec<T, N>;

        /**
         * @brief Type alias for mtx2
         */
        using mtx2 = math::mtx2<T>;

        /**
         * @brief Type alias for mtx3
         */
        using mtx3 = math::mtx3<T>;

        /**
         * @brief Type alias for mtx4
         */
        using mtx4 = math::mtx4<T>;

        /**
         * @brief Type alias for circular interval
         */
        using cinterval = math::cinterval<T>;

        /**
         * @brief Type alias for interval
         */
        using interval = math::interval<T>;

        /**
         * @brief Type alias for aabb2
         */
        using aabb2 = geom::aabb2<T>;

        /**
         * @brief Type alias for aabb3
         */
        using aabb3 = geom::aabb3<T>;

        /**
         * @brief Type alias for segment2
         */
        using segment2 = geom::segment2<T>;

        /**
         * @brief Type alias for segment3
         */
        using segment3 = geom::segment3<T>;

        /**
         * @brief Type alias for ray2
         */
        using ray2 = geom::ray2<T>;

        /**
         * @brief Type alias for ray3
         */
        using ray3 = geom::ray3<T>;

        /**
         * @brief Type alias for polyline2
         */
        using polyline2 = geom::polyline2<T>;

        /**
         * @brief Type alias for polygon
         */
        using polygon = geom::polygon<T>;

        /**
         * @brief Type alias for holygon
         */
        using holygon = geom::holygon<T>;

        /**
         * @brief Type alias for scamera
         */
        using scamera = cam::scamera<T>;

        /**
         * @brief Type alias for frustum
         */
        using frustum = cam::frustum<T>;

    };

    using gpu = instantiate_types<gpu_float_t>;

} // stf

// default instantiated types for projects that don't have to worry about precision
using stff = stf::instantiate_types<float>;
using stfd = stf::instantiate_types<double>;
using stfi = stf::instantiate_types<int>;
using stfu = stf::instantiate_types<uint32_t>;