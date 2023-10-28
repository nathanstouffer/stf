#pragma once

#include <cmath>

#include <algorithm>

#include "stf/alg/spherical.hpp"
#include "stf/cam/scamera.hpp"
#include "stf/gfx/color.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace alg {

    // clamp time to [0, 1]
    template<typename T>
    inline T clamp_time(T t)
    {
        return std::clamp(t, T(0), T(1));    // clamped
    }

    // smooth out time for smoothstep
    template<typename T>
    inline T smooth_time(T t)
    {
        T t = clamp_time(t);                // clamped
        return t * t * (T(3) - T(2) * t);   // smoothed
    }

    // multiply and add
    template<typename T>
    inline T mad(T a, T b, T c)
    {
        return a * b + c;
    }

    // negate the result of multiply and subtract
    template<typename T>
    inline T nms(T a, T b, T c)
    {
        return c - a * b;
    }

    template<typename T>
    inline T lerp(T a, T b, T t)
    {
        return mad(t, b, nms(t, a, a));
    }

    template<typename T>
    inline T lerp_inv(T a, T b, T x)
    {
        return (x - a) / (b - a);
    }

    template<typename T>
    inline T lerpstep(T a, T b, T t)
    {
        return lerp(a, b, clamp_time(t));
    }

    template<typename T>
    inline T smoothstep(T a, T b, T t)
    {
        return lerp(a, b, smooth_time(t));
    }

    template<typename T>
    inline T sigmoid(T x)
    {
        return T(1) / (T(1) + std::exp(-x));
    }

    template<class T, size_t N>
    inline math::vec<T, N> clamp(math::vec<T, N> const& vec, math::vec<T, N> const& min, math::vec<T, N> const& max)
    {
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = std::clamp(vec[i], min[i], max[i]);
        }
        return result;
    }

    template<class T, size_t N>
    inline math::vec<T, N> clamp(math::vec<T, N> const& vec, T const min, T const max)
    {
        return clamp(vec, math::vec<T, N>(min), math::vec<T, N>(max));
    }

    template<class T, size_t N>
    inline math::vec<T, N> lerp(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
    {
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = lerp(a[i], b[i], t);
        }
        return result;
    }

    template<class T, size_t N>
    inline math::vec<T, N> lerpstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
    {
        return lerp(a, b, clamp_time(t))
    }

    template<class T, size_t N>
    inline math::vec<T, N> smoothstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
    {
        return lerp(a, b, smooth_time(t));
    }

    inline gfx::rgba clamp(gfx::rgba const& lhs, gfx::rgba::num_t min, gfx::rgba::num_t max)
    {
        return gfx::rgba(clamp(lhs.as_vec(), min, max));
    }

    inline gfx::rgba lerp(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        return gfx::rgba(lerp(lhs.as_vec(), rhs.as_vec(), t));
    }

    inline gfx::rgba lerpstep(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        return gfx::rgba(lerpstep(lhs.as_vec(), rhs.as_vec(), t));
    }

    inline gfx::rgba smoothstep(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        return gfx::rgba(smoothstep(lhs.as_vec(), rhs.as_vec(), t));
    }

    // TODO (stouff) write this blend function 
    //inline gfx::rgba blend(gfx::rgba const& current, gfx::rgba const& writing)

    template<typename T>
    inline cam::scamera<T> lerp(cam::scamera<T> const& lhs, cam::scamera<T> const& rhs, T const t)
    {
        cam::scamera<T> result;
        result.eye    = lerp(lhs.eye, rhs.eye, t);
        result.theta  = lerp(lhs.theta, closest_equiv_angle(lhs.theta, rhs.theta), t);
        result.phi    = lerp(lhs.phi, closest_equiv_angle(lhs.phi, rhs.phi), t);
        result.near   = lerp(lhs.near, rhs.far, t);
        result.far    = lerp(lhs.far, rhs.far, t);
        result.aspect = lerp(lhs.aspect, rhs.aspect, t);
        result.fov    = lerp(lhs.fov, rhs.fov, t);
        return result;
    }

    template<typename T>
    inline cam::scamera<T> lerpstep(cam::scamera<T> const& lhs, cam::scamera<T> const& rhs, T const t)
    {
        return lerp(lhs, rhs, clamp_time(t));
    }

    template<typename T>
    inline cam::scamera<T> smoothstep(cam::scamera<T> const& lhs, cam::scamera<T> const& rhs, T const t)
    {
        return lerp(lhs, rhs, smooth_time(t));
    }

} // alg
} // stf