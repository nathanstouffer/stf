#pragma once

#include <memory>

#include "stf/math/interval.hpp"

namespace stf::spatial
{

	// TODO (stouff) figure out a way to use the intervals as keys and return the values associated with the keys that are hit
	template<typename T>
	class interval_tree
	{
	public:

		using interval_t = math::interval<T>;

	public:

		explicit interval_tree(std::vector<interval_t> const& intervals) : m_intervals(intervals), m_root(interval_tree::construct(m_intervals)) {}

		// TODO (stouff) write query function

	private:

		// TODO (stouff) populate with sorted lists of the intervals that contain the pivot
		struct center_t
		{
			T pivot;

		};

		// TODO (stouff) think about how to structure this correctly
		struct tree
		{

			center_t center;

			// left and right subtrees
			std::unique_ptr<tree> left = nullptr;
			std::unique_ptr<tree> right = nullptr;

			inline bool has_left() const { return left; }
			inline bool has_right() const { return right; }

		};

	private:

		// TODO (stouff) actually write this function -- this is just a shell
		static std::unique_ptr<tree> construct(std::vector<interval_t> const& intervals)
		{
			// base case where there are no intervals
			if (intervals.empty()) { return nullptr; }

			std::vector<interval_t> left;
			std::vector<interval_t> right;

			// TODO (stouff) actually compute the center
			center_t center;

			return std::make_unique<tree>(std::move(center), interval_tree::construct(left), interval_tree::construct(right));
		}

	private:

		std::vector<interval_t> m_intervals;
		std::unique_ptr<tree> m_root;

	};

}