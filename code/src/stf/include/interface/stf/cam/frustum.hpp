#pragma once

#include "stf/cam/scamera.hpp"
#include "stf/geom/hyperplane.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

namespace stf::cam
{

    // TODO write this class once we have a plane and aabb class
    template<typename T>
    class frustum final
    {
    public:

        using vec_t = math::vec3<T>;
        using aabb_t = geom::aabb3<T>;

    public:

        explicit frustum(scamera<T> const& camera) : frustum(vertices(camera)) {}

        bool contains(vec_t const& point) const
        {
            // check if any plane
            for (size_t i = 0; i < c_num_planes; ++i)
            {
                if (m_planes[i].side(point) < math::constants<T>::zero) { return false; }
            }
            return true;    // fallthrough to return true
        }

        bool contains(aabb_t const& aabb) const
        {
            // TODO (stouff) write this function
        }

        // TODO (stouff) remark about false positives
        bool intersects(aabb_t const& aabb) const
        {
            // TODO (stouff) write this function
        }

    private:

        static constexpr size_t c_num_planes = 6;

        struct vertices final
        {
            // points defining the near plane
            vec_t ntl; vec_t ntr;
            vec_t nbl; vec_t nbr;
            // points defining the far plane
            vec_t ftl; vec_t ftr;
            vec_t fbl; vec_t fbr;

            explicit vertices(scamera<T> const& camera)
            {
                // compute camera basis vectors
                vec_t look = camera.look();
                vec_t up = camera.up();
                vec_t right = camera.right();

                // compute points on the near plane
                {
                    T half_height = camera.near * std::tan(camera.aspect);
                    T half_width = half_height * camera.aspect;

                    vec_t center = camera.eye + look * camera.near;
                    vec_t delta_up = up * half_height;
                    vec_t delta_right = right * half_width;

                    ntl = center + delta_up - delta_right; ntr = center + delta_up + delta_right;
                    nbl = center - delta_up - delta_right; nbr = center - delta_up + delta_right;
                }

                // compute points on the far plane
                {
                    T half_height = camera.far * std::tan(camera.aspect);
                    T half_width = half_height * camera.aspect;

                    vec_t center = camera.eye + look * camera.far;
                    vec_t delta_up = up * half_height;
                    vec_t delta_right = right * half_width;

                    ftl = center + delta_up - delta_right; ftr = center + delta_up + delta_right;
                    fbl = center - delta_up - delta_right; fbr = center - delta_up + delta_right;
                }
            }

        };

        // unscoped enum so we can use it as an array index
        enum side : size_t
        {
            NEAR   = 0,
            FAR    = 1,
            LEFT   = 2,
            RIGHT  = 3,
            TOP    = 4,
            BOTTOM = 5
        };

    private:

        explicit frustum(vertices const& verts)
        {
            // TODO (stouff) write this function
        }

        geom::plane m_planes[c_num_planes];

    };

} // stf::cam