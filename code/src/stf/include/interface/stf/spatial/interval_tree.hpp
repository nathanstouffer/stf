#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"

namespace stf::spatial
{

	template<typename T, typename V>
	class interval_tree
	{
	public:

		using interval_t = math::interval<T>;

		struct entry_t
		{
			interval_t interval;
			V value;

			entry_t(interval_t const& _interval, V const& _value) : interval(_interval), value(_value) {}

		};

	public:

		explicit interval_tree(std::vector<entry_t>&& entries) : m_entries(std::move(entries)), m_root(interval_tree::construct(factory_args(m_entries))) {}

		// TODO (stouff) write query function

	private:

		using entry_ptr_t = entry_t const*;

		struct center_t
		{
			T pivot;

			// these two lists are the same set of intervals (all containing the pivot), just sorted differently
			std::vector<entry_ptr_t> lesser;					// sorted by begin point (ascending)
			std::vector<entry_ptr_t> greater;					// sorted by end point (descending)

			center_t(T const _pivot) : pivot(_pivot) {}

			inline bool is_empty() const { return lesser.empty(); }

			void insert(entry_ptr_t entry)
			{
				lesser.push_back(entry);
				greater.push_back(entry);
			}

			void sort()
			{
				std::sort(lesser.begin(), lesser.end(), [](entry_ptr_t lhs, entry_ptr_t rhs) { return lhs->interval.a < rhs->interval.a; });
				std::sort(greater.begin(), greater.end(), [](entry_ptr_t lhs, entry_ptr_t rhs) { return lhs->interval.b > rhs->interval.b; });
			}

		};

		// TODO (stouff) think about how to structure this correctly
		struct node_t
		{

			center_t center;

			// left and right subtrees
			std::unique_ptr<node_t> left;
			std::unique_ptr<node_t> right;

			node_t(center_t&& center, std::unique_ptr<node_t> left, std::unique_ptr<node_t> right) : center(std::move(center)), left(std::move(left)), right(std::move(right)) {}

			inline bool has_left() const { return left; }
			inline bool has_right() const { return right; }

		};

	private:

		struct sortable_t
		{
			T x;
			entry_ptr_t entry;

			sortable_t(T const _x, entry_ptr_t _entry) : x(_x), entry(_entry) {}

		};

		struct factory_args
		{
			std::vector<entry_ptr_t> intervals;
			std::vector<sortable_t> sorted;

			factory_args() = default;
			factory_args(std::vector<entry_t> const& entries) : intervals(interval_tree::pointers(entries)), sorted(interval_tree::sorted(entries)) {}
		};

		static inline T median(std::vector<sortable_t> const& sorted)
		{
			size_t mid = sorted.size() / 2;
			if (sorted.size() & size_t(1)) // if odd, just return the mid
			{
				return sorted[mid].x;
			}
			else						// if even, return the average of the middle two
			{
				return math::constants<T>::half * (sorted[mid - 1].x + sorted[mid].x);
			}
		}

		static std::unique_ptr<node_t> construct(factory_args const& args)
		{
			// base case where there are no intervals
			if (args.intervals.empty()) { return nullptr; }

			factory_args left{};
			factory_args right{};
			center_t center(interval_tree::median(args.sorted));

			// iterate over intervals, adding to the appropriate node
			for (entry_ptr_t entry : args.intervals)
			{
				if (entry->interval.b < center.pivot) { left.intervals.push_back(entry); }			// interval is entirely to the left
				else if (center.pivot < entry->interval.a) { right.intervals.push_back(entry); }		// interval is entirely to the right
				else { center.insert(entry); }														// invterval contains the pivot
			}

			// iterate over sorted points, adding to the appropriate node
			for (sortable_t sortable : args.sorted)
			{
				if (sortable.entry->interval.b < center.pivot) { left.sorted.push_back(sortable); }			// interval is entirely to the left
				else if (center.pivot < sortable.entry->interval.a) { right.sorted.push_back(sortable); }	// interval is entirely to the right
			}

			center.sort();		// sort the intervals that contain the pivot

			return std::make_unique<node_t>(std::move(center), interval_tree::construct(left), interval_tree::construct(right));
		}

		// TODO (stouff) there is probably an STL algorithm for this
		static std::vector<entry_ptr_t> pointers(std::vector<entry_t> const& entries)
		{
			std::vector<entry_ptr_t> ptrs;
			ptrs.reserve(entries.size());
			for (entry_t const& entry : entries) { ptrs.push_back(&entry); }
			return ptrs;
		}

		// TODO (stouff) there is probably an STL algorithm for this
		static std::vector<sortable_t> sorted(std::vector<entry_t> const& entries)
		{
			std::vector<sortable_t> sortable;
			sortable.reserve(entries.size());
			for (entry_t const& entry : entries)
			{
				sortable.push_back(sortable_t(entry.interval.a, &entry));
				sortable.push_back(sortable_t(entry.interval.b, &entry));
			}
			std::sort(sortable.begin(), sortable.end(), [](sortable_t const& lhs, sortable_t const& rhs) { return lhs.x < rhs.x; });
			return sortable;
		}

	private:

		std::vector<entry_t> m_entries;
		std::unique_ptr<node_t> m_root;

	};

}