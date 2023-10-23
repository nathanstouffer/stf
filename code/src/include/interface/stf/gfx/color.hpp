#pragma once

#include <cinttypes>

#include <algorithm>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace gfx {

    // TODO (stouff) possibly template this?
    struct color
    {
    public:

        using num_t = float;

        num_t r;
        num_t g;
        num_t b;
        num_t a;

        color() : color(0, 0, 0, 1) {}
        explicit color(num_t const t) : color(t, t, t, t) {}
        explicit color(num_t const t, num_t const _a) : color(t, t, t, _a) {}
        color(num_t const _r, num_t const _g, num_t const _b) : color(_r, _g, _b, 1) {}
        color(num_t const _r, num_t const _g, num_t const _b, num_t const _a) : r(_r), g(_g), b(_b), a(_a) {}
        explicit color(math::vec<num_t, 3> vec) : color(math::vec<num_t, 4>(vec, 1)) {}
        explicit color(math::vec<num_t, 4> vec) : color(vec.x, vec.y, vec.z, vec.w) {}

    public:

        static inline uint8_t to_byte(num_t const x)
        {
            // compute t -- we clamp to just less than 1 so we max out at 255
            num_t t = std::clamp(x, num_t(0), num_t(1 - 0.00001));
            return uint8_t(t * 256);
        }

        static inline num_t from_byte(uint32_t const hex, uint32_t const shift)
        {
            uint8_t const value = uint8_t((hex & (0xFF << shift)) >> shift);
            return num_t(value) / num_t(255);
        }

    public:

        inline explicit operator math::vec<color::num_t, 4>() const { return math::vec<color::num_t, 4>(r, g, b, a); }

        inline uint32_t rgba() const { return (to_byte(r) << 24) | (to_byte(g) << 16) | (to_byte(b) << 8) | (to_byte(a)); }
        inline uint32_t abgr() const { return (to_byte(a) << 24) | (to_byte(b) << 16) | (to_byte(g) << 8) | (to_byte(r)); }
        inline uint32_t argb() const { return (to_byte(a) << 24) | (to_byte(r) << 16) | (to_byte(g) << 8) | (to_byte(b)); }

        static inline color from_rgba(uint32_t rgba) { return color(from_byte(rgba, 24), from_byte(rgba, 16), from_byte(rgba, 8),  from_byte(rgba, 0)); }
        static inline color from_abgr(uint32_t abgr) { return color(from_byte(abgr, 0),  from_byte(abgr, 8),  from_byte(abgr, 16), from_byte(abgr, 24)); }
        static inline color from_argb(uint32_t argb) { return color(from_byte(argb, 16), from_byte(argb, 8),  from_byte(argb, 0),  from_byte(argb, 24)); }

    };

    inline bool const equ(color const& lhs, color const& rhs, color::num_t eps)
    {
        return equ(static_cast<math::vec<color::num_t, 4>>(lhs), static_cast<math::vec<color::num_t, 4>>(rhs), eps);
    }

    inline bool const neq(color const& lhs, color const& rhs, color::num_t eps)
    {
        return !equ(lhs, rhs, eps);
    }

    inline bool const operator==(color const& lhs, color const& rhs)
    {
        return equ(lhs, rhs, math::constants<color::num_t>::tol);
    }

    inline bool const operator!=(color const& lhs, color const& rhs)
    {
        return !(lhs == rhs);
    }

    std::ostream& operator<<(std::ostream& s, color const& rhs)
    {
        return s << "[ " << rhs.r << ", " << rhs.g << ", " << rhs.b << ", " << rhs.a << " ]";
    }
    
    // TODO (stouff) class for HSV and other ways of representing color

} // gfx
} // stf