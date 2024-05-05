#pragma once

#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T, size_t N>
    struct ray final
    {

        using vec_t = math::vec<T, N>;

    public:

        vec_t point;
        vec_t direction;

        ray(vec_t const& _point, vec_t const& _direction) : point(_point), direction(_direction) {}

        inline ray& normalize() { direction.normalize(); return *this; }

    };

    // delete invalid ray specializations
    template<typename T> struct ray<T, 0> { ray() = delete; };

    // type aliases for ease of use
    template<typename T> using ray2 = ray<T, 2>;
    template<typename T> using ray3 = ray<T, 3>;

} // stf::geom