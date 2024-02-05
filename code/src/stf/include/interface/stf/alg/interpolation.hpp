#pragma once

#include <cmath>

#include <algorithm>

#include "stf/cam/scamera.hpp"
#include "stf/gfx/color.hpp"
#include "stf/math/spherical.hpp"
#include "stf/math/vector.hpp"

namespace stf::alg
{

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
        T const s = clamp_time(t);          // clamped
        return s * s * (T(3) - T(2) * s);   // smoothed
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
    inline T cubic_bezier(T const a, T const b, T const c, T const d, T const t)
    {
        // TODO simplify this implementation to just one polynomial
        // first round of lerps
        T const a1 = lerp(a, b, t);
        T const b1 = lerp(b, c, t);
        T const c1 = lerp(c, d, t);

        // second round of lerps
        T const a2 = lerp(a1, b1, t);
        T const b2 = lerp(b1, c1, t);

        // final lerp
        return lerp(a2, b2, t);
    }

    // function to interpolate between p0 and p1 using cubic hermite splines (https://en.wikipedia.org/wiki/Cubic_Hermite_spline)
    // the spline function f(t) is defined on [0, 1] and satisfies the following constraints
    //    * f(0) = p0 and f(1) = p1
    //    * f'(0) = m0 and f'(1) = m1
    // so consecutive splines can be made C^1 at the boundary. because this function assumes a domain of [0, 1], the derivatives
    // passed in (m0 and m1) must be scaled by the length of the actual interval to get accurate results
    template<typename T>
    inline T cubic_hermite_spline(T const p0, T const m0, T const p1, T const m1, T const t)
    {
        T t_squared = t * t;
        T t_cubed = t_squared * t;

        // compute basis values
        T b0 = T(2) * t_cubed - T(3) * t_squared + T(1);
        T b1 = t_cubed - T(2) * t_squared + t;
        T b2 = T(-2) * t_cubed + T(3) * t_squared;
        T b3 = t_cubed - t_squared;

        return b0 * p0 + b1 * m0 + b2 * p1 + b3 * m1;
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
        return lerp(a, b, clamp_time(t));
    }

    template<class T, size_t N>
    inline math::vec<T, N> smoothstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
    {
        return lerp(a, b, smooth_time(t));
    }

    template<typename T, size_t N>
    inline math::vec<T, N> cubic_bezier(math::vec<T, N> const a, math::vec<T, N> const b, math::vec<T, N> const c, math::vec<T, N> const d, T const t)
    {
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = cubic_bezier(a[i], b[i], c[i], d[i], t);
        }
        return result;
    }

    template<typename T, size_t N>
    inline math::vec<T, N> cubic_hermite_spline(math::vec<T, N> const p0, math::vec<T, N> const m0, math::vec<T, N> const p1, math::vec<T, N> const m1, T const t)
    {
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = cubic_hermite_spline(p0[i], m0[i], p1[i], m1[i], t);
        }
        return result;
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

    inline gfx::rgba blend(gfx::rgba const& current, gfx::rgba const& writing)
    {
        gfx::rgba blended = current;
        blended.r = lerp(blended.r, writing.r, writing.a);
        blended.g = lerp(blended.g, writing.g, writing.a);
        blended.b = lerp(blended.b, writing.b, writing.a);
        blended.a = std::max(blended.a, writing.a);
        return blended;
    }

    template<typename T>
    inline cam::scamera<T> lerp(cam::scamera<T> const& lhs, cam::scamera<T> const& rhs, T const t)
    {
        cam::scamera<T> result;
        result.eye    = lerp(lhs.eye, rhs.eye, t);
        result.theta  = lerp(lhs.theta, math::closest_equiv_angle(lhs.theta, rhs.theta), t);
        result.phi    = lerp(lhs.phi, math::closest_equiv_angle(lhs.phi, rhs.phi), t);
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

} // stf::alg