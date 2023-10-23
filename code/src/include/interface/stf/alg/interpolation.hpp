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

    inline gfx::rgba clamp(gfx::rgba const& lhs, gfx::rgba::num_t min, gfx::rgba::num_t max)
    {
        using vec_t = math::vec<gfx::rgba::num_t, 4>;
        return gfx::rgba(clamp(static_cast<vec_t>(lhs), min, max));
    }

    inline gfx::rgba lerp(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        using vec_t = math::vec<gfx::rgba::num_t, 4>;
        return gfx::rgba(lerp(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    inline gfx::rgba lerpstep(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        using vec_t = math::vec<gfx::rgba::num_t, 4>;
        return gfx::rgba(lerpstep(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    inline gfx::rgba smoothstep(gfx::rgba const& lhs, gfx::rgba const& rhs, gfx::rgba::num_t t)
    {
        using vec_t = math::vec<gfx::rgba::num_t, 4>;
        return gfx::rgba(smoothstep(static_cast<vec_t>(lhs), static_cast<vec_t>(rhs), t));
    }

    // TODO (stouff) write this blend function 
    //inline gfx::rgba blend(gfx::rgba const& current, gfx::rgba const& writing)


} // alg
} // stf