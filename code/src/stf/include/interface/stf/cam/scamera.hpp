#pragma once

#include "stf/geom/ray.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interpolation.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/scalar.hpp"
#include "stf/math/spherical.hpp"
#include "stf/math/transform.hpp"
#include "stf/math/vector.hpp"

/**
 * @file scamera.hpp
 * @brief A file containing a class that represents a simple camera defined by a point in R^3 and a look direction in spherical coordinates
 */

namespace stf::cam
{

    /**
     * @brief Struct to represent a simple camera -- one where the right vector is always in the plane normal
     * to (0, 0, 1). The look direction is represented by spherical coordinates with the eye as the origin
     * @tparam T Number type (eg float)
     * @note All angles are in radians
     */
    template<typename T>
    struct scamera final
    {
    public:

        /**
         * @brief Type alias for a vector
         */
        using vec_t = math::vec3<T>;

        /**
         * @brief Type alias for a matrix
         */
        using mtx_t = math::mtx4<T>;

    public:

        /// @cond DELETED
        static vec_t constexpr c_default_eye = vec_t(0);
        static T constexpr c_default_theta = math::constants<T>::half_pi;
        static T constexpr c_default_phi = math::constants<T>::pi;
        static T constexpr c_default_nearp = T(0.1);
        static T constexpr c_default_farp = T(1000);
        static T constexpr c_default_fov = T(45) * math::constants<T>::pi / T(180);
        static T constexpr c_default_aspect = T(16) / T(9);
        /// @endcond

    public:

        /**
         * @brief The position of the camera
         */
        vec_t eye;

        /**
         * @brief The angle of the look direction in the xy-plane
         */
        T theta;

        /**
         * @brief The angle of the look direction off the z-axis
         */
        T phi;

        /**
         * @brief The near plane
         */
        T nearp;

        /**
         * @brief The far plane
         */
        T farp;

        /**
         * @brief The aspect ratio (w / h)
         */
        T aspect;

        /**
         * @brief The field of view (in y)
         */
        T fov;
        
        /**
         * @brief Fully qualified scamera constructor
         */
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _nearp, T const _farp, T const _aspect, T const _fov) :
            eye(_eye), theta(_theta), phi(_phi), nearp(_nearp), farp(_farp), aspect(_aspect), fov(_fov) {}

        /**
         * @brief Default constructor
         */
        explicit scamera() : scamera(c_default_eye) {}

        /**
         * @brief Construct from a position
         * @param [in] _eye 
         */
        explicit scamera(vec_t const& _eye) : scamera(_eye, c_default_theta) {}

        /**
         * @brief Construct from a position and theta
         * @param [in] _eye 
         * @param [in] _theta 
         */
        scamera(vec_t const& _eye, T const _theta) : scamera(_eye, _theta, c_default_phi) {}

        /**
         * @brief Construct from a position and orientation
         * @param [in] _eye 
         * @param [in] _theta 
         * @param [in] _phi 
         */
        scamera(vec_t const& _eye, T const _theta, T const _phi) : scamera(_eye, _theta, _phi, c_default_nearp, c_default_farp) {}

        /**
         * @brief Construct from a position, orientation, and near/far plane
         * @param [in] _eye 
         * @param [in] _theta 
         * @param [in] _phi 
         * @param [in] _nearp
         * @param [in] _farp
         */
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _nearp, T const _farp) : scamera(_eye, _theta, _phi, _nearp, _farp, c_default_aspect) {}

        /**
         * @brief Construct from a position, orientation, near/far plane, and aspect ratio
         * @param [in] _eye 
         * @param [in] _theta 
         * @param [in] _phi 
         * @param [in] _nearp 
         * @param [in] _farp 
         * @param [in] _aspect 
         */
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _nearp, T const _farp, T const _aspect) : scamera(_eye, _theta, _phi, _nearp, _farp, _aspect, c_default_fov) {}
        
        /**
         * @brief Construct from a theta
         * @param [in] _theta 
         */
        explicit scamera(T const _theta) : scamera(c_default_eye, _theta) {}
        
        /**
         * @brief Construct from an orientation
         * @param [in] _theta 
         * @param [in] _phi 
         */
        scamera(T const _theta, T const _phi) : scamera(c_default_eye, _theta, _phi) {}

        /**
         * @brief Compute the look direction of the camera
         * @return The look direction
         */
        vec_t look() const { return math::unit_vector(theta, phi); }

        /**
         * @brief Compute the up direction of the camera
         * @return The up direction
         */
        vec_t up() const { return math::unit_vector(theta, phi - math::constants<T>::half_pi); }

        /**
         * @brief Compute the right direction of the camera
         * @return The right direction
         */
        vec_t right() const { return math::cross(look(), up()); }

        /**
         * @brief Compute the ray from the eye passing through a specified point on the screen
         * @param [in] uv The UV coordinates of the screen point that the ray passes through
         * @note When @p uv is (0, 0), the ray passes through the top left corner
         * @note When @p uv is (1, 1), the ray passes through the bottom right corner
         * @return The ray from @p eye passing through @p uv
         */
        geom::ray3<T> ray(math::vec2<T> const& uv) const
        {
            // compute the ndc coords (the y-direction must be flipped
            math::vec2<T> ndc = math::constants<T>::two * uv - math::vec2<T>(math::constants<T>::one);
            ndc.y *= -math::constants<T>::one;

            T const half_height = std::tan(fov * math::constants<T>::half);
            T const half_width = aspect * half_height;

            vec_t f = look();
            vec_t r = half_width  * ndc.x * right();
            vec_t u = half_height * ndc.y * up();
            return geom::ray3<T>(eye, math::normalized(f + r + u));
        }

        /**
         * @brief Compute the view matrix for the scamera
         * @return The view matrix for @p this
         */
        mtx_t view() const { return math::view<T>(eye, look(), right(), up()); }

        /**
         * @brief Compute the perspective projection matrix for the scamera
         * @return The perspective projection matrix for @p this
         */
        mtx_t perspective() const { return math::perspective<T>(fov, aspect, nearp, farp); }

        /**
         * @brief Compute the inverse of the view matrix for the scamera
         * @return The inverse of the view matrix for @p this
         */
        mtx_t inv_view() const { return view().inverted(); }

        /**
         * @brief Compute the inverse of the perspective projection matrix for the scamera
         * @return The inverse of the perspective projection matrix for @p this
         */
        mtx_t inv_perspective() const { perspective().inverted(); }

    };

    /**
     * @brief Compute whether the distance between @p lhs and @p rhs is less than or equal to @p eps
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] eps The epsilon distance to use when computating approximate equality
     * @return Whether or not @p lhs and @p rhs are closer than @p eps
     */
    template<typename T>
    inline bool equ(scamera<T> const& lhs, scamera<T> const& rhs, T eps)
    {
        return equ(lhs.eye, rhs.eye, eps)
                && math::equ(lhs.theta, rhs.theta, eps)
                && math::equ(lhs.phi, rhs.phi, eps)
                && math::equ(lhs.nearp, rhs.nearp, eps)
                && math::equ(lhs.farp, rhs.farp, eps)
                && math::equ(lhs.aspect, rhs.aspect, eps)
                && math::equ(lhs.fov, rhs.fov, eps);
    }

    /**
     * @brief Compute whether the distance between @p lhs and @p rhs is strictly greater than eps
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] eps The epsilon distance to use when computating approximate equality
     * @return Whether or not @p lhs and @p rhs are further apart than @p eps
     */
    template<typename T>
    inline bool neq(scamera<T> const& lhs, scamera<T> const& rhs, T eps)
    {
        return !equ(lhs, rhs, eps);
    }

    /**
     * @brief Compute whether @p lhs is approximately equal to @p rhs (uses constants<T>::tol as epsilon)
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs and @p rhs are approximately equal
     */
    template<typename T>
    inline bool operator==(scamera<T> const& lhs, scamera<T> const& rhs)
    {
        return equ(lhs, rhs, math::constants<T>::tol);
    }

    /**
     * @brief Compute whether @p lhs is approximately not equal to @p rhs (uses constants<T>::tol as epsilon)
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] lhs
     * @param [in] rhs
     * @return Whether or not @p lhs and @p rhs are approximately not equal
     */
    template<typename T>
    inline bool operator!=(scamera<T> const& lhs, scamera<T> const& rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Linearly interpolate scameras
     * @note @p t is not clamped to [0, 1] (use @ref lerpstep if that is desired)
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] t
     * @return The interpolated scamera
     */
    template<typename T>
    inline scamera<T> lerp(scamera<T> const& lhs, scamera<T> const& rhs, T const t)
    {
        scamera<T> result;
        result.eye    = math::lerp(lhs.eye, rhs.eye, t);
        result.theta  = math::lerp(lhs.theta, math::closest_equiv_angle(rhs.theta, lhs.theta), t);
        result.phi    = math::lerp(lhs.phi, math::closest_equiv_angle(rhs.phi, lhs.phi), t);
        result.nearp  = math::lerp(lhs.nearp, rhs.nearp, t);
        result.farp   = math::lerp(lhs.farp, rhs.farp, t);
        result.aspect = math::lerp(lhs.aspect, rhs.aspect, t);
        result.fov    = math::lerp(lhs.fov, rhs.fov, t);
        return result;
    }

    /**
     * @brief Linearly interpolate scameras (clamped to the endpoint values)
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] t
     * @return The interpolated scamera
     */
    template<typename T>
    inline scamera<T> lerpstep(scamera<T> const& lhs, scamera<T> const& rhs, T const t)
    {
        return lerp(lhs, rhs, math::clamp_time(t));
    }

    /**
     * @brief Interpolate smoothly between the scamera endpoints
     * @tparam T Number type (eg float)
     * @param [in] lhs
     * @param [in] rhs
     * @param [in] t
     * @return The interpolated scamera
     */
    template<typename T>
    inline scamera<T> smoothstep(scamera<T> const& lhs, scamera<T> const& rhs, T const t)
    {
        return lerp(lhs, rhs, math::smooth_time(t));
    }

    /**
     * @brief Orbits @p camera around @p focus by @p delta_phi and @p delta_theta
     * @tparam T Number type (eg float)
     * @param [in] camera The camera to be orbited
     * @param [in] focus Center point of the orbit
     * @param [in] delta_phi
     * @param [in] delta_theta
     * @note Angles @p delta_phi and @p delta_theta are spherical coordinates measured with @p focus as the origin
     * @return The orbited scamera
     */
    template<typename T>
    inline scamera<T> orbit(scamera<T> const& camera, math::vec3<T> const& focus, T const delta_phi, T const delta_theta)
    {
        // copy camera state so unaffected values are preserved
        scamera<T> result = camera;

        // rotate the eye and adjust heading and pitch appropriately
        result.eye = math::orbit(camera.eye, focus, camera.right(), -delta_phi, delta_theta);
        result.theta += delta_theta;
        result.phi += delta_phi;

        // return result
        return result;
    }

    /**
     * @brief Write the sccamera @p rhs to the std::ostream @p s
     * @tparam T Number type (eg float)
     * @param [in,out] s
     * @param [in] rhs
     * @return A reference to @p s
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& s, scamera<T> const& rhs)
    {
        s << "[";
        s << " eye: " << rhs.eye;
        s << " theta: " << rhs.theta;
        s << " phi: " << rhs.phi;
        s << " nearp: " << rhs.nearp;
        s << " farp: " << rhs.farp;
        s << " aspect: " << rhs.aspect;
        s << " fov: " << rhs.fov;
        s << " ]";
        return s;
    }

} // stf::cam