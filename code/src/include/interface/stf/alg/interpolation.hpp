#pragma once

#include <cmath>

#include <algorithm>

#include "stf/gfx/color.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace alg {

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
    inline T lerpstep(T a, T b, T x)
    {
        return lerp(a, b, std::clamp(x, T(0), T(1)));
    }

    template<typename T>
    inline T smoothstep(T a, T b, T x)
    {
        T t = std::clamp(t, T(0), T(1));    // clamped
        T s = t * t * (T(3) - T(2) * t);    // smooth
        return lerp(a, b, s);
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
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = lerpstep(a[i], b[i], t);
        }
        return result;
    }

    template<class T, size_t N>
    inline math::vec<T, N> smoothstep(math::vec<T, N> const& a, math::vec<T, N> const& b, T const t)
    {
        math::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = smoothstep(a[i], b[i], t);
        }
        return result;
    }

    inline gfx::color clamp(gfx::color const& lhs, gfx::color::num_t min, gfx::color::num_t max)
    {
        using vec_t = math::vec<gfx::color::num_t, 4>;
        return gfx::color(clamp(static_cast<vec_t>(lhs), min, max));
    }

    inline gfx::color lerp(gfx::color const& lhs, gfx::color const& rhs, gfx::color::num_t t)
    {
        using vec_t = math::vec<gfx::color::num_t, 4>;
        return gfx::color(lerp(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    inline gfx::color lerpstep(gfx::color const& lhs, gfx::color const& rhs, gfx::color::num_t t)
    {
        using vec_t = math::vec<gfx::color::num_t, 4>;
        return gfx::color(lerpstep(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    inline gfx::color smoothstep(gfx::color const& lhs, gfx::color const& rhs, gfx::color::num_t t)
    {
        using vec_t = math::vec<gfx::color::num_t, 4>;
        return gfx::color(smoothstep(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    // TODO (stouff) write this blend function 
    //inline gfx::color blend(gfx::color const& current, gfx::color const& writing)


} // alg
} // stf