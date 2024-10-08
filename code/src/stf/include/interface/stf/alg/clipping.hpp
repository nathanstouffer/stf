#pragma once

#include "stf/geom/polyline.hpp"

/**
 * @file clipping.hpp
 * @brief A file containing functions that clip geometric objects
 */

/// @cond DELETED
namespace stf::alg::guts
{

	enum region_code : int
	{
		INSIDE = 0x0,
		LEFT   = 0x1,
		RIGHT  = 0x2,
		BOTTOM = 0x4,
		TOP    = 0x8,
	};

	template<typename T>
	region_code code(geom::aabb2<T> const& box, math::vec2<T> const& point)
	{
		region_code region = region_code::INSIDE;

		region_code x = region_code::INSIDE;
		if      (point.x < box.min.x) { x = region_code::LEFT;  }
		else if (box.max.x < point.x) { x = region_code::RIGHT; }

		region_code y = region_code::INSIDE;
		if      (point.y < box.min.y) { y = region_code::BOTTOM; }
		else if (box.max.y < point.y) { y = region_code::TOP;  }

		return static_cast<region_code>(x | y);
	}

}
/// @endcond

namespace stf::alg
{

	// TODO (stouff) possibly rename this to include the cohen-sutherland naming
	template<typename T>
	bool clip(geom::aabb2<T> const& box, geom::segment2<T>& seg)
	{
		guts::region_code code0 = guts::code(box, seg.a);
		guts::region_code code1 = guts::code(box, seg.b);

		while (true)	// TODO (stouff) avoid infinite loop. I think we can place a finite bound on the number of time the loop should run
		{
			bool outside = code0 | code1;
			if (!outside)			// if both points are inside the box, accept the segment
			{
				return true;
			}
			else if (code0 & code1)	// if both points share a region, reject the segment
			{
				return false;
			}
			else							// otherwise, pick a point and clip it to a line defined by the box
			{
				math::vec2<T> point;
				guts::region_code code = code1 > code0 ? code1 : code0;
				// TODO (stouff) write comment about how we avoid dividing by 0
				if (code & guts::region_code::TOP)
				{
					point.x = seg.a.x + (box.max.y - seg.a.y) * seg.slope_inv();
					point.y = box.max.y;
				}
				else if (code & guts::region_code::BOTTOM)
				{
					point.x = seg.a.x + (box.min.y - seg.a.y) * seg.slope_inv();
					point.y = box.min.y;
				}
				else if (code & guts::region_code::RIGHT)
				{
					point.x = box.max.x;
					point.y = seg.a.y + (box.max.x - seg.a.x) * seg.slope();
				}
				else if (code & guts::region_code::LEFT)
				{
					point.x = box.min.x;
					point.y = seg.a.y + (box.min.x - seg.a.x) * seg.slope();
				}

				// update the segment endpoint
				if (code == code0)
				{
					seg.a = point;
					code0 = guts::code(box, seg.a);
				}
				else
				{
					seg.b = point;
					code1 = guts::code(box, seg.b);
				}
			}
		}
	}

	// TODO (stouff) possibly write the liang-barsky alg?

} // stf::alg