#pragma once

#include <array>

#include "stf/cam/scamera.hpp"
#include "stf/geom/hyperplane.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/vector.hpp"

/**
 * @file frustum.hpp
 * @brief A file containing a class that represents a frustumed pyramid in R^3
 */

namespace stf::cam
{

    /**
     * @brief Struct to represent a frustumed pyramid in R^3
     * @tparam T Number type (eg float)
     */
    template<typename T>
    class frustum final
    {
    public:

        /**
         * @brief Type alias for a vector
         */
        using vec_t = math::vec3<T>;

        /**
         * @brief Type alias for an aabb
         */
        using aabb_t = geom::aabb3<T>;

        /**
         * @brief Type alias for a plane
         */
        using plane_t = geom::plane<T>;

        /**
         * @brief The number of planes that define a frustum
         */
        static constexpr size_t c_num_planes = 6;

    public:

        /**
         * @brief Construct a frustum from a scamera
         */
        explicit frustum(scamera<T> const& camera) : frustum(vertices(camera)) {}

        /**
         * @brief Compute whether or not a point is contained in the frustum
         * @param [in] point The query point
         * @return Whethor or not @p point is inside in @p this
         */
        bool contains(vec_t const& point) const
        {
            // check if any plane does not contain the point
            for (size_t i = 0; i < c_num_planes; ++i)
            {
                if (m_planes[i].side(point) < math::constants<T>::zero) { return false; }
            }
            return true;    // fallthrough to return true
        }

        /**
         * @brief Compute whether or not an aabb is contained in the frustum
         * @param [in] aabb The query aabb
         * @return Whether or not @p aabb is contained in @p this
         */
        bool contains(aabb_t const& aabb) const
        {
            for (size_t i = 0; i < c_num_planes; ++i)
            {
                // check if the extremity in the direction of the anti-normal is contained in the halfspace
                plane_t const& plane = m_planes[i];
                vec_t extremity = aabb.extremity(-plane.normal());
                bool contained = plane.side(extremity) >= math::constants<T>::zero;
                if (!contained) { return false; }
            }
            return true;    // fallthrough to return true
        }

        /**
         * @brief Compute whether or not an aabb intersects a frustum
         * @param [in] aabb The query aabb
         * @note This algorithm identifies false positives (returns true for some frustum/aabb that don't actually intersect)
         * @return Whether or not @p aabb intersect @p this
         */
        bool intersects_fast(aabb_t const& aabb) const
        {
            // TODO (stouff) make an aabb intersection query
            for (size_t i = 0; i < c_num_planes; ++i)
            {
                // check if the extremity in the direction of the normal is contained in the halfspace
                plane_t const& plane = m_planes[i];
                vec_t extremity = aabb.extremity(plane.normal());
                bool contained = plane.side(extremity) >= math::constants<T>::zero;
                if (!contained) { return false; }
            }
            // TODO (stouff) make a test for box containing no frustum vertices
            return true;    // fallthrough to return true
        }

        /**
         * @brief Provide const access to the planes that define the frustum
         */
        std::array<plane_t, c_num_planes> const& planes() const { return m_planes; }

    private:

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
            m_planes[FAR]    = geom::fit_plane(verts.ftl, verts.fbl, verts.ftr);
            m_planes[NEAR]   = geom::plane<T>(verts.ntl, -m_planes[FAR].normal());     // define near plane as a function of the far plane to avoid precision issues
            m_planes[LEFT]   = geom::fit_plane(verts.ftl, verts.ntl, verts.fbl);
            m_planes[RIGHT]  = geom::fit_plane(verts.ftr, verts.fbr, verts.ntr);
            m_planes[TOP]    = geom::fit_plane(verts.ftl, verts.ftr, verts.ntl);
            m_planes[BOTTOM] = geom::fit_plane(verts.fbr, verts.fbl, verts.nbr);
        }

        std::array<plane_t, c_num_planes> m_planes;

    };

} // stf::cam