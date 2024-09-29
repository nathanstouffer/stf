#pragma once

#include <array>
#include <vector>

#include "stf/cam/scamera.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/obb.hpp"
#include "stf/geom/hyperplane.hpp"
#include "stf/math/basis.hpp"
#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"
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
         * @brief Type alias for an obb
         */
        using obb_t = geom::obb3<T>;

        /**
         * @brief Type alias for a plane
         */
        using plane_t = geom::plane<T>;

        /**
         * @brief Type alias for a basis
         */
        using basis_t = math::basis<T, 3>;

        /**
         * @brief Type alias for an interval
         */
        using interval_t = math::interval<T>;

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
            if (m_aabb.intersects(aabb))
            {
                // check if any frustum plane entirely excludes the box
                for (size_t i = 0; i < c_num_planes; ++i)
                {
                    // check if the extremity in the direction of the normal is contained in the halfspace
                    plane_t const& plane = m_planes[i];
                    vec_t extremity = aabb.extremity(plane.normal());
                    bool contained = plane.side(extremity) >= math::constants<T>::zero;
                    if (!contained) { return false; }
                }

                // check if any box plane entirely excludes the frustum
                {
                    std::array<vec_t, 8> verts =
                    {
                        // near points
                        m_vertices.ntl, m_vertices.ntr,
                        m_vertices.nbl, m_vertices.nbr,
                        // far points
                        m_vertices.ftl, m_vertices.ftr,
                        m_vertices.fbl, m_vertices.fbr
                    };

                    for (size_t d = 0; d < 3; ++d)  // iterate over each dimension (x, y, and z)
                    {
                        // check the plane at the minimum of the box that has a normal in the +d direction
                        {
                            // count the number of frustum vertices outside the box
                            size_t outside = 0;
                            for (vec_t const& vert : verts)
                            {
                                outside += vert[d] < aabb.min[d] ? 1 : 0;
                            }
                            if (outside == 8) { return false; }
                        }

                        // check the plane at the maximum of the box that has a normal in the -d direction
                        {
                            // count the number of frustum vertices outside the box
                            size_t outside = 0;
                            for (vec_t const& vert : verts)
                            {
                                outside += aabb.max[d] < vert[d] ? 1 : 0;
                            }
                            if (outside == 8) { return false; }
                        }
                    }
                }

                // if we arrive here, we were not able to prove that the frustum/aabb do not intersect. so we must assume that
                // they do intersect, though this maybe be incorrect (resulting in a false positive)
                return true;    // fallthrough to return true
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Compute whether or not an aabb intersects a frustum
         * @param [in] aabb The query aabb
         * @return Whether or not @p aabb intersect @p this
         */
        bool const intersects(aabb_t const& aabb) const
        {
            if (intersects_fast(aabb))  // if the fast check returns true, do a more thorough check to avoid false positives
            {
                for (vec_t const& axis : m_canonical_separation_axes)
                {
                    if (axis.length_squared() > math::constants<T>::zero)
                    {
                        bool separates = !projection(axis).intersects(aabb.projection(axis));
                        if (separates)
                        {
                            return false;
                        }
                    }
                }
                return true;    // fallthrough to true
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Compute whether or not an obb intersects a frustum
         * @param [in] obb The query obb
         * @return Whether or not @p obb intersect @p this
         */
        bool const intersects(obb_t const& obb) const
        {
            for (vec_t const& axis : frustum::possible_axes(obb.basis(), m_planes, m_vertices))
            {
                if (axis.length_squared() > math::constants<T>::zero)
                {
                    bool separates = !projection(axis).intersects(obb.projection(axis));
                    if (separates)
                    {
                        return false;
                    }
                }
            }
            return true;    // fallthrough to true
        }

        /**
         * @brief Compute the projection of a @ref frustum onto an axis
         * @param [in] axis
         * @return The interval of projection onto the axis
         * @note @p axis is assumed to be a unit vector
         */
        interval_t const projection(vec_t const& axis) const
        {
            interval_t interval(math::constants<T>::pos_inf, math::constants<T>::neg_inf);
            std::array<vec_t, 8> points =
            {
                // near points                      // far points
                m_vertices.ntl, m_vertices.ntr,     m_vertices.ftl, m_vertices.ftr,
                m_vertices.nbl, m_vertices.nbr,     m_vertices.fbl, m_vertices.fbr,
            };
            for (vec_t const& point : points)
            {
                T const l = math::dot(point, axis);
                interval.a = std::min(interval.a, l);
                interval.b = std::max(interval.b, l);
            }
            return interval;
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
                    T half_height = camera.near * std::tan(math::constants<T>::half * camera.fov);
                    T half_width = half_height * camera.aspect;

                    vec_t center = camera.eye + look * camera.near;
                    vec_t delta_up = up * half_height;
                    vec_t delta_right = right * half_width;

                    ntl = center + delta_up - delta_right; ntr = center + delta_up + delta_right;
                    nbl = center - delta_up - delta_right; nbr = center - delta_up + delta_right;
                }

                // compute points on the far plane
                {
                    T half_height = camera.far * std::tan(math::constants<T>::half * camera.fov);
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
        
        static std::array<vec_t, 26> possible_axes(basis_t const& basis, std::array<plane_t, c_num_planes> const& planes, vertices const& verts)
        {
            std::array<vec_t, 26> axes =
            {
                // box normals
                basis[0],
                basis[1],
                basis[2],
                // frustum normals
                planes[side::FAR].normal(),
                planes[side::LEFT].normal(),
                planes[side::RIGHT].normal(),
                planes[side::TOP].normal(),
                planes[side::BOTTOM].normal(),
            };
            // add axes for cross products between pairs of edges from each polyhedra (the box normals and edge directions are the same)
            for (size_t d = 0; d < 3; ++d)
            {
                size_t offset = 8 + d * 6;  // offset by how many axes have been written to the array
                axes[offset + 0] = math::cross(basis[d], math::normalized(verts.ftr - verts.ftl));
                axes[offset + 1] = math::cross(basis[d], math::normalized(verts.ftr - verts.fbr));
                axes[offset + 2] = math::cross(basis[d], math::normalized(verts.ftl - verts.ntl));
                axes[offset + 3] = math::cross(basis[d], math::normalized(verts.ftr - verts.ntr));
                axes[offset + 4] = math::cross(basis[d], math::normalized(verts.fbl - verts.nbl));
                axes[offset + 5] = math::cross(basis[d], math::normalized(verts.fbr - verts.nbr));
            }
            return axes;
        }

    private:

        explicit frustum(vertices const& verts) : m_vertices(verts)
        {
            m_planes[FAR]    = geom::fit_plane(verts.ftl, verts.fbl, verts.ftr);
            m_planes[NEAR]   = geom::plane<T>(verts.ntl, -m_planes[FAR].normal());     // define near plane as a function of the far plane to avoid precision issues
            m_planes[LEFT]   = geom::fit_plane(verts.ftl, verts.ntl, verts.fbl);
            m_planes[RIGHT]  = geom::fit_plane(verts.ftr, verts.fbr, verts.ntr);
            m_planes[TOP]    = geom::fit_plane(verts.ftl, verts.ftr, verts.ntl);
            m_planes[BOTTOM] = geom::fit_plane(verts.fbr, verts.fbl, verts.nbr);

            std::vector<vec_t> points =
            {
                // near points          // far points
                verts.ntl, verts.ntr,   verts.ftl, verts.ftr,
                verts.nbl, verts.nbr,   verts.fbl, verts.fbr,
            };
            m_aabb = aabb_t::fit(points);

            m_canonical_separation_axes = frustum::possible_axes(math::canonical_basis<T, 3>(), m_planes, m_vertices);
        }

        std::array<plane_t, c_num_planes> m_planes;
        vertices m_vertices;
        aabb_t m_aabb;
        std::array<vec_t, 26> m_canonical_separation_axes;      // separation axes to test when intersecting with an aabb

    };

} // stf::cam