#pragma once

#include <cinttypes>

#include <algorithm>

#include "stf/math/constants.hpp"
#include "stf/math/interpolation.hpp"
#include "stf/math/vector.hpp"

/**
 * @file color.hpp
 * @brief A file containing various color classes along with associated functions
 */

namespace stf::gfx
{

/**
 * @brief A class that represents a color as four floats
 * @todo Possibly template this class?
 */
struct rgba final
{
  public:
    /**
     * @brief The amount of color in the r component -- in the range [0, 1]
     */
    float r;

    /**
     * @brief The amount of color in the g component -- in the range [0, 1]
     */
    float g;

    /**
     * @brief The amount of color in the b component -- in the range [0, 1]
     */
    float b;

    /**
     * @brief The amount of color in the a component -- in the range [0, 1]
     */
    float a;

    /**
     * @brief Default constructor -- initializes to all black with full opacity
     */
    rgba() : rgba(0, 0, 0, 1) {}

    /**
     * @brief Construct from a single float -- all values are initialized to @p t
     * @param [in] t
     */
    explicit rgba(float const t) : rgba(t, t, t, t) {}

    /**
     * @brief Construct color from a single float and specify alpha separately
     * @param [in] t
     * @param [in] _a
     */
    explicit rgba(float const t, float const _a) : rgba(t, t, t, _a) {}

    /**
     * @brief Construct from three floats -- alpha is initialized to 1
     * @param [in] _r
     * @param [in] _g
     * @param [in] _b
     */
    rgba(float const _r, float const _g, float const _b) : rgba(_r, _g, _b, 1) {}

    /**
     * @brief Construct from each component explicitly
     * @param [in] _r
     * @param [in] _g
     * @param [in] _b
     * @param [in] _a
     */
    rgba(float const _r, float const _g, float const _b, float const _a)
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a)
    {
    }

    /**
     * @brief Construct from a  vec3 -- used to initialize r, g, and b
     * @param [in] vec
     */
    explicit rgba(math::vec3<float> vec) : rgba(math::vec4<float>(vec, 1)) {}

    /**
     * @brief Cosntruct from a  vec4 -- used to initialize each component
     * @param vec
     */
    explicit rgba(math::vec4<float> vec) : rgba(vec.x, vec.y, vec.z, vec.w) {}

  public:
    /**
     * @brief Convert a float in [0, 1] to an 8-bit integer in [0, 255]
     * @param [in] x
     * @return The corresponding 8-bit integer
     */
    static inline uint8_t to_hex(float const x)
    {
        // compute t -- we clamp to just less than 1 so we max out at 255
        float t = std::clamp(x, float(0), float(1 - 0.00001));
        return uint8_t(t * 256);
    }

    /**
     * @brief Convert a single byte of a 32-bit integer to
     * @param [in] hex The initial 32-bit integer representing the color
     * @param [in] shift Left-shift the mask by this many bits
     * @return The byte converted to a float in [0, 1]
     */
    static inline float from_hex(uint32_t const hex, uint32_t const shift)
    {
        uint8_t const value = uint8_t((hex & (0xFF << shift)) >> shift);
        return float(value) / float(255);
    }

  public:
    /**
     * @brief Compute the color as a vec4
     * @return The color as a vec4
     */
    inline math::vec4<float> as_vec() const { return math::vec4<float>(r, g, b, a); }

    /**
     * @brief Conversion operator to a vec4
     */
    inline explicit operator math::vec4<float>() const { return as_vec(); }

    /**
     * @brief Convert to 32-bit integer in RGBA format
     * @return RGBA 32-bit integer
     */
    inline uint32_t to_hex_rgba() const
    {
        return (to_hex(r) << 24) | (to_hex(g) << 16) | (to_hex(b) << 8) | (to_hex(a));
    }

    /**
     * @brief Convert to 32-bit integer in ABGR format
     * @return ABGR 32-bit integer
     */
    inline uint32_t to_hex_abgr() const
    {
        return (to_hex(a) << 24) | (to_hex(b) << 16) | (to_hex(g) << 8) | (to_hex(r));
    }

    /**
     * @brief Convert to 32-bit integer in ARGB format
     * @return ARGB 32-bit integer
     */
    inline uint32_t to_hex_argb() const
    {
        return (to_hex(a) << 24) | (to_hex(r) << 16) | (to_hex(g) << 8) | (to_hex(b));
    }

    /**
     * @brief Construct a @ref rgba from a 32-bit RGBA integer
     * @param [in] hex_rgba
     * @return Constructed @ref rgba value
     */
    static inline rgba from_hex_rgba(uint32_t hex_rgba)
    {
        return rgba(from_hex(hex_rgba, 24), from_hex(hex_rgba, 16), from_hex(hex_rgba, 8),
                    from_hex(hex_rgba, 0));
    }

    /**
     * @brief Construct a @ref rgba from a 32-bit ABGR integer
     * @param [in] hex_abgr
     * @return Constructed @ref rgba value
     */
    static inline rgba from_hex_abgr(uint32_t hex_abgr)
    {
        return rgba(from_hex(hex_abgr, 0), from_hex(hex_abgr, 8), from_hex(hex_abgr, 16),
                    from_hex(hex_abgr, 24));
    }

    /**
     * @brief Construct a @ref rgba from a 32-bit ARGB integer
     * @param [in] hex_argb
     * @return Constructed @ref rgba value
     */
    static inline rgba from_hex_argb(uint32_t hex_argb)
    {
        return rgba(from_hex(hex_argb, 16), from_hex(hex_argb, 8), from_hex(hex_argb, 0),
                    from_hex(hex_argb, 24));
    }
};

/**
 * @brief Compute whether the distance between @p lhs and @p rhs is less than or equal to @p eps
 * @param [in] lhs
 * @param [in] rhs
 * @param [in] eps The epsilon distance to use when computating approximate equality
 * @return Whether or not @p lhs and @p rhs are closer than @p eps
 */
inline bool equ(rgba const& lhs, rgba const& rhs, float eps)
{
    return equ(static_cast<math::vec4<float>>(lhs), static_cast<math::vec4<float>>(rhs), eps);
}

/**
 * @brief Compute whether the distance between @p lhs and @p rhs is strictly greater than eps
 * @param [in] lhs
 * @param [in] rhs
 * @param [in] eps The epsilon distance to use when computating approximate equality
 * @return Whether or not @p lhs and @p rhs are further apart than @p eps
 */
inline bool neq(rgba const& lhs, rgba const& rhs, float eps)
{
    return !equ(lhs, rhs, eps);
}

/**
 * @brief Compute whether @p lhs is approximately equal to @p rhs (uses constants<T>::tol as
 * epsilon)
 * @param [in] lhs
 * @param [in] rhs
 * @return Whether or not @p lhs and @p rhs are approximately equal
 */
inline bool operator==(rgba const& lhs, rgba const& rhs)
{
    return equ(lhs, rhs, math::constants<float>::tol);
}

/**
 * @brief Compute whether @p lhs is approximately not equal to @p rhs (uses constants<T>::tol as
 * epsilon)
 * @param [in] lhs
 * @param [in] rhs
 * @return Whether or not @p lhs and @p rhs are approximately not equal
 */
inline bool operator!=(rgba const& lhs, rgba const& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Clamp a @ref rgba
 * @param [in] lhs
 * @param [in] min
 * @param [in] max
 * @return The clamped @ref rgba
 */
inline rgba clamp(rgba const& lhs, float min, float max)
{
    return rgba(clamp(lhs.as_vec(), min, max));
}

/**
 * @brief Linearly interpolate @ref rgba
 * @param [in] lhs
 * @param [in] rhs
 * @param [in] t
 * @return The interpolated @ref rgba
 */
inline rgba lerp(rgba const& lhs, rgba const& rhs, float t)
{
    return rgba(lerp(lhs.as_vec(), rhs.as_vec(), t));
}

/**
 * @brief Linearly interpolate @ref rgba (clamped to the endpoint values)
 * @param [in] lhs
 * @param [in] rhs
 * @param [in] t
 * @return The interpolated @ref rgba
 */
inline rgba lerpstep(rgba const& lhs, rgba const& rhs, float t)
{
    return rgba(lerpstep(lhs.as_vec(), rhs.as_vec(), t));
}

/**
 * @brief Interpolate smoothly between the @ref rgba endpoints
 * @param [in] lhs
 * @param [in] rhs
 * @param [in] t
 * @return The interpolated @ref rgba
 */
inline rgba smoothstep(rgba const& lhs, rgba const& rhs, float t)
{
    return rgba(smoothstep(lhs.as_vec(), rhs.as_vec(), t));
}

/**
 * @brief Alpha blend @p writing into @p current
 * @param [in] current
 * @param [in] writing
 * @return The blended @ref rgba
 */
inline rgba blend(rgba const& current, rgba const& writing)
{
    rgba blended = current;
    blended.r = math::lerp(blended.r, writing.r, writing.a);
    blended.g = math::lerp(blended.g, writing.g, writing.a);
    blended.b = math::lerp(blended.b, writing.b, writing.a);
    blended.a = std::max(blended.a, writing.a);
    return blended;
}

/**
 * @brief Write the rgba @p rhs to the std::ostream @p s
 * @param [in,out] s
 * @param [in] rhs
 * @return A reference to @p s
 */
inline std::ostream& operator<<(std::ostream& s, rgba const& rhs)
{
    return s << "[ " << rhs.r << ", " << rhs.g << ", " << rhs.b << ", " << rhs.a << " ]";
}

// TODO class for hsv and other ways of representing color

} // namespace stf::gfx