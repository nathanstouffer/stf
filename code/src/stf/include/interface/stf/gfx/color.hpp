#pragma once

#include <cinttypes>

#include <algorithm>

#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace gfx {

    // TODO (stouff) possibly template this?
    struct rgba
    {
    public:

        using num_t = float;

        num_t r;
        num_t g;
        num_t b;
        num_t a;

        rgba() : rgba(0, 0, 0, 1) {}
        explicit rgba(num_t const t) : rgba(t, t, t, t) {}
        explicit rgba(num_t const t, num_t const _a) : rgba(t, t, t, _a) {}
        rgba(num_t const _r, num_t const _g, num_t const _b) : rgba(_r, _g, _b, 1) {}
        rgba(num_t const _r, num_t const _g, num_t const _b, num_t const _a) : r(_r), g(_g), b(_b), a(_a) {}
        explicit rgba(math::vec<num_t, 3> vec) : rgba(math::vec<num_t, 4>(vec, 1)) {}
        explicit rgba(math::vec<num_t, 4> vec) : rgba(vec.x, vec.y, vec.z, vec.w) {}

    public:

        static inline uint8_t to_hex(num_t const x)
        {
            // compute t -- we clamp to just less than 1 so we max out at 255
            num_t t = std::clamp(x, num_t(0), num_t(1 - 0.00001));
            return uint8_t(t * 256);
        }

        static inline num_t from_hex(uint32_t const hex, uint32_t const shift)
        {
            uint8_t const value = uint8_t((hex & (0xFF << shift)) >> shift);
            return num_t(value) / num_t(255);
        }

    public:

        inline math::vec<rgba::num_t, 4> as_vec() const { return math::vec<rgba::num_t, 4>(r, g, b, a); }
        inline explicit operator math::vec<rgba::num_t, 4>() const { return as_vec(); }

        inline uint32_t to_hex_rgba() const { return (to_hex(r) << 24) | (to_hex(g) << 16) | (to_hex(b) << 8) | (to_hex(a)); }
        inline uint32_t to_hex_abgr() const { return (to_hex(a) << 24) | (to_hex(b) << 16) | (to_hex(g) << 8) | (to_hex(r)); }
        inline uint32_t to_hex_argb() const { return (to_hex(a) << 24) | (to_hex(r) << 16) | (to_hex(g) << 8) | (to_hex(b)); }

        static inline rgba from_hex_rgba(uint32_t hex_rgba) { return rgba(from_hex(hex_rgba, 24), from_hex(hex_rgba, 16), from_hex(hex_rgba, 8),  from_hex(hex_rgba, 0)); }
        static inline rgba from_hex_abgr(uint32_t hex_abgr) { return rgba(from_hex(hex_abgr, 0),  from_hex(hex_abgr, 8),  from_hex(hex_abgr, 16), from_hex(hex_abgr, 24)); }
        static inline rgba from_hex_argb(uint32_t hex_argb) { return rgba(from_hex(hex_argb, 16), from_hex(hex_argb, 8),  from_hex(hex_argb, 0),  from_hex(hex_argb, 24)); }

    };

    inline bool const equ(rgba const& lhs, rgba const& rhs, rgba::num_t eps)
    {
        return equ(static_cast<math::vec<rgba::num_t, 4>>(lhs), static_cast<math::vec<rgba::num_t, 4>>(rhs), eps);
    }

    inline bool const neq(rgba const& lhs, rgba const& rhs, rgba::num_t eps)
    {
        return !equ(lhs, rhs, eps);
    }

    inline bool const operator==(rgba const& lhs, rgba const& rhs)
    {
        return equ(lhs, rhs, math::constants<rgba::num_t>::tol);
    }

    inline bool const operator!=(rgba const& lhs, rgba const& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& s, rgba const& rhs)
    {
        return s << "[ " << rhs.r << ", " << rhs.g << ", " << rhs.b << ", " << rhs.a << " ]";
    }

    // TODO (stouff) class for hsv and other ways of representing color

} // gfx
} // stf