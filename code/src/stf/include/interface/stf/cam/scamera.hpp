#pragma once

#include "stf/math/constants.hpp"
#include "stf/math/matrix.hpp"
#include "stf/math/scalar.hpp"
#include "stf/math/vector.hpp"

namespace stf {
namespace cam {

    // Struct to represent a simple camera -- one where the right vector is always in the plane normal
    // to (0, 0, 1). The look direction is represented by spherical coordinates with the eye as the origin
    template<typename T>
    struct scamera
    {
    public:

        // type aliases to reduce verbosity
        using vec_t = math::vec3<T>;
        using mtx_t = math::mtx4<T>;

    public:

        static vec_t constexpr c_default_eye = vec_t(0);

        static T constexpr c_default_theta = math::constants<T>::half_pi;
        static T constexpr c_default_phi = math::constants<T>::pi;
        static T constexpr c_default_near = T(0.1);
        static T constexpr c_default_far = T(1000);
        static T constexpr c_default_fov = T(45) * math::constants<T>::pi / T(180);
        static T constexpr c_default_aspect = T(16) / T(9);

    public:

        vec_t eye;
        T theta;
        T phi;
        T near;
        T far;
        T aspect;
        T fov;
        
        // fully qualified constructor
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _near, T const _far, T const _aspect, T const _fov) :
            eye(_eye), theta(_theta), phi(_phi), near(_near), far(_far), aspect(_aspect), fov(_fov) {}

        // call through constrctors
        scamera() : scamera(c_default_eye) {}
        scamera(vec_t const& _eye) : scamera(_eye, c_default_theta) {}
        scamera(vec_t const& _eye, T const _theta) : scamera(_eye, _theta, c_default_phi) {}
        scamera(vec_t const& _eye, T const _theta, T const _phi) : scamera(_eye, _theta, _phi, c_default_near, c_default_far) {}
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _near, T const _far) : scamera(_eye, _theta, _phi, _near, _far, c_default_aspect) {}
        scamera(vec_t const& _eye, T const _theta, T const _phi, T const _near, T const _far, T const _aspect) : scamera(_eye, _theta, _phi, _near, _far, _aspect, c_default_fov) {}
        scamera(T const _theta) : scamera(c_default_eye, _theta) {}
        scamera(T const _theta, T const _phi) : scamera(c_default_eye, _theta, _phi) {}

        vec_t look() const { return math::unit_vector(theta, phi); }
        vec_t up() const { return math::unit_vector(theta, phi - math::constants<T>::half_pi); }
        vec_t right() const { return math::cross(look(), up()); }

        // TODO (stouff) write these matrix methods
        // mtx_t view() const;
        // mtx_t proj() const;
        // mtx_t view_proj() const;

        // mtx_t inv_view() const;
        // mtx_t inv_proj() const;
        // mtx_t inv_view_proj() const;

    };

    template<typename T>
    inline bool const equ(scamera<T> const& lhs, scamera<T> const& rhs, T eps)
    {
        return equ(lhs.eye, rhs.eye, eps)
                && math::equ(lhs.theta, rhs.theta, eps)
                && math::equ(lhs.phi, rhs.phi, eps)
                && math::equ(lhs.near, rhs.near, eps)
                && math::equ(lhs.far, rhs.far, eps)
                && math::equ(lhs.aspect, rhs.aspect, eps)
                && math::equ(lhs.fov, rhs.fov, eps);
    }

    template<typename T>
    inline bool const neq(scamera<T> const& lhs, scamera<T> const& rhs, T eps)
    {
        return !equ(lhs, rhs, eps);
    }

    template<typename T>
    inline bool const operator==(scamera<T> const& lhs, scamera<T> const& rhs)
    {
        return equ(lhs, rhs, math::constants<T>::tol);
    }

    template<typename T>
    inline bool const operator!=(scamera<T> const& lhs, scamera<T> const& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& s, scamera<T> const& rhs)
    {
        s << "[";
        s << " eye: " << rhs.eye;
        s << " theta: " << rhs.theta;
        s << " phi: " << rhs.phi;
        s << " near: " << rhs.near;
        s << " far: " << rhs.far;
        s << " aspect: " << rhs.aspect;
        s << " fov: " << rhs.fov;
        s << " ]";
        return s;
    }

} // cam
} // stf