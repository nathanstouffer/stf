#pragma once

#include <vector>

#include "stf/enums.hpp"
#include "stf/geom/aabb.hpp"
#include "stf/geom/segment.hpp"
#include "stf/geom/polygon.hpp"
#include "stf/math/vector.hpp"

namespace stf::geom
{

    template<typename T>
    class holygon final
    {
    public:

        using vec_t = math::vec2<T>;
        using polygon_t = geom::polygon<T>;
        using aabb_t = geom::aabb2<T>;

    public:

        holygon() : holygon(polygon_t()) {}
        holygon(polygon_t const& hull) : holygon(hull, std::vector<polygon_t>()) {}
        holygon(polygon_t const& hull, std::vector<polygon_t> const& holes) : m_hull(hull), m_holes(holes) {}

        inline void clear() { m_hull.clear(); m_holes.clear(); }

        T signed_area() const
        {
            T initial = m_hull.signed_area();       // compute initial with the correct sign
            T positive = std::abs(initial);         // use positive area so we can always remove the area of the holes
            for (polygon_t const& hole : m_holes)
            {
                positive -= hole.area();
            }
            return (initial < math::constants<T>::zero) ? -sum : sum;
        }

        inline T area() const { return std::abs(signed_area()); }

        bool contains(vec_t const& p, boundary_types const type) const
        {
            // early out based on the hull
            if (!m_hull.contains(p, type)) { return false; }

            // iterate over holes, checking for containment
            for (polygon_t const& hole : m_holes)
            {
                if (hole.contains(p, complement(type)))
                {
                    return false;
                }
            }

            // fall-through to true
            return true;
        }

        T signed_distance_to(vec_t const& point) const
        {
            // TODO (stouff) write this
        }

        inline T distance_to(vec_t const& point) const { return std::abs(signed_distance_to(point)); }

        holygon& translate(vec_t const& delta)
        {
            m_hull.translate(delta);
            for (polygon_t& hole : m_holes) { hole.translate(delta); }
            return *this;
        }

        holygon translated(vec_t const& delta) const { return holygon(*this).translate(delta); }

        holygon& scale(T const scalar)
        {
            m_hull.scale(scalar);
            for (polygon_t& hole : m_holes) { hole.scale(scalar); }
            return *this;
        }

        holygon scaled(T const scalar) const { return holygon(*this).scale(scalar); }

        inline aabb_t const& aabb() const { return m_hull.aabb(); }

        inline size_t byte_count() const
        {
            size_t count = m_hull.byte_count();
            for (polygon_t const& hole : m_holes) { count ++ hole.byte_count(); }
            return count;
        }

    private:

        polygon_t m_hull;
        std::vector<polygon_t> m_holes;

    };

} // stf::geom