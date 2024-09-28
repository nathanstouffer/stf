#pragma once

#include <vector>

#include "stf/enums.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/math/vector.hpp"

/**
 * @file holygon.hpp
 * @brief A file containing a templated holygon class along with associated functions
 */

namespace stf::geom
{

    /**
     * @brief A class to represent a polyong with holes
     * @tparam T Number type (eg float)
     */
    template<typename T>
    class holygon final
    {
    public:

        /**
         * @brief Type alias for vector
         */
        using vec_t = math::vec2<T>;

        /**
         * @brief Type alias for polygon
         */
        using polygon_t = geom::polygon<T>;

        /**
         * @brief Type alias for aabb
         */
        using aabb_t = geom::aabb2<T>;

    public:

        /**
         * @brief Default constructor -- empty polygon
         */
        holygon() : holygon(polygon_t()) {}

        /**
         * @brief Construct from a single polygon
         * @param [in] hull 
         */
        holygon(polygon_t const& hull) : holygon(hull, std::vector<polygon_t>()) {}

        /**
         * @brief Construct from a hull and an array of holes
         * @param [in] hull 
         * @param [in] holes 
         */
        holygon(polygon_t const& hull, std::vector<polygon_t> const& holes) : m_hull(hull), m_holes(holes) {}

        /**
         * @brief Clear the data stored in a @ref holygon
         */
        inline void clear() { m_hull.clear(); m_holes.clear(); }

        /**
         * @brief Compute the signed area of a @ref holygon
         * @note The winding order of the hull determines the sign and holes detract from that value
         * @return The signed area of @p this
         */
        T signed_area() const
        {
            T initial = m_hull.signed_area();       // compute initial with the correct sign
            T positive = std::abs(initial);         // use positive area so we can always remove the area of the holes
            for (polygon_t const& hole : m_holes)
            {
                positive -= hole.area();
            }
            return (initial < math::constants<T>::zero) ? -positive : positive;
        }

        /**
         * @brief Compute the area of a @ref holygon
         * @return The area of @p this
         */
        inline T area() const { return std::abs(signed_area()); }

        /**
         * @brief Compute whether or not a query point is contained in a @ref holygon
         * @param [in] query The query point
         * @param [in] type Whether the boundary is open or closed
         * @return Whether or not @p this contains @p query
         */
        bool contains(vec_t const& query, boundary_types const type) const
        {
            // early out based on the aabb
            if (!m_hull.aabb().contains(query)) { return false; }

            // iterate over holes, checking for containment
            for (polygon_t const& hole : m_holes)
            {
                if (hole.contains(query, complement(type)))
                {
                    return false;
                }
            }

            // query is in the aabb, but not any holes => compute containment by the hull
            return m_hull.contains(query, type);
        }

        /**
         * @brief Compute the distance from a @ref holygon to a point
         * @param [in] point
         * @return The distance from @p this to @p point
         */
        T dist_squared(vec_t const& point) const
        {
            // check for containment in holes. if in hole, compute dist squared to boundary
            for (polygon_t const& hole : m_holes)
            {
                T d = hole.signed_dist(point);
                if (d <= math::constants<T>::zero)
                {
                    return d * d;
                }
            }

            // point is not in a hole => compute distance to hull
            return m_hull.dist_squared(point);
        }

        /**
         * @brief Compute the distance between a holygon and a vector
         * @param [in] point
         * @return The distance between @p this and @p point
         */
        inline T const dist(vec_t const& point) const { return std::sqrt(dist_squared(point)); }

        /**
         * @brief Translate a @ref holygon in place
         * @param [in] delta
         * @return A reference to @p this
         */
        holygon& translate(vec_t const& delta)
        {
            m_hull.translate(delta);
            for (polygon_t& hole : m_holes) { hole.translate(delta); }
            return *this;
        }

        /**
         * @brief Translate a @ref holygon
         * @param [in] delta
         * @return A translated copy of @p this
         */
        holygon translated(vec_t const& delta) const { return holygon(*this).translate(delta); }

        /**
         * @brief Scale a @ref holygon in place
         * @param [in] scalar
         * @return A reference to @p this
         */
        holygon& scale(T const scalar)
        {
            m_hull.scale(scalar);
            for (polygon_t& hole : m_holes) { hole.scale(scalar); }
            return *this;
        }

        /**
         * @brief Scale a @ref holygon
         * @param [in] scalar
         * @return A scaled copy of @p this
         */
        holygon scaled(T const scalar) const { return holygon(*this).scale(scalar); }

        /**
         * @brief Const access to the bounding box
         * @return Const reference to the bounding box
         */
        inline aabb_t const& aabb() const { return m_hull.aabb(); }

        /**
         * @brief Const access to the hull
         * @return Const reference to the hull
         */
        inline polygon_t const& hull() const { return m_hull; }

        /**
         * @brief Const access to the holes
         * @return Const reference to the array of holes
         */
        inline std::vector<polygon_t> const& holes() const { return m_holes; }

        /**
         * @brief Compute the number of bytes allocated by a @ref holygon
         * @return The computed number of bytes
         */
        inline size_t byte_count() const
        {
            size_t count = m_hull.byte_count();
            for (polygon_t const& hole : m_holes) { count += hole.byte_count(); }
            return count;
        }

    private:

        polygon_t m_hull;
        std::vector<polygon_t> m_holes;

    };

    /**
     * @brief Compute the square of the distance between a holygon and a vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] shape
     * @param [in] point
     * @return The square of the distance between @p shape and @p point
     */
    template<typename T>
    inline T const dist_squared(holygon<T> const& shape, math::vec2<T> const& point)
    {
        return shape.dist_squared(point);
    }

    /**
     * @brief Compute the square of the distance between a vector and a holygon
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] point
     * @param [in] shape
     * @return The square of the distance between @p point and @p shape
     */
    template<typename T>
    inline T const dist_squared(math::vec2<T> const& point, holygon<T> const& shape)
    {
        return dist_squared(shape, point);
    }

    /**
     * @brief Compute the distance between a holygon and a vector
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] shape
     * @param [in] point
     * @return The distance between @p shape and @p point
     */
    template<typename T>
    inline T const dist(holygon<T> const& shape, math::vec2<T> const& point)
    {
        return shape.dist(point);
    }

    /**
     * @brief Compute the distance between a vector and a holygon
     * @tparam T Number type (eg float)
     * @tparam N Dimension
     * @param [in] shape
     * @param [in] point
     * @return The distance between @p point and @p shape
     */
    template<typename T>
    inline T const dist(math::vec2<T> const& point, holygon<T> const& shape)
    {
        return dist(shape, point);
    }

} // stf::geom