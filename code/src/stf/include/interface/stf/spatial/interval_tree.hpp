#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"

namespace stf::spatial
{

	// TODO make this class copyable
	// TODO allocate nodes in chunks instead of one-by-one
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

			inline bool operator==(entry_t const& rhs) const { return interval == rhs.interval && value == rhs.value; }

		};

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

		struct query_iterator
		{

			struct position_t
			{
				using iterator = typename std::vector<entry_ptr_t>::const_iterator;
				
				node_t const* node;
				iterator it;

				position_t(node_t const* _node, iterator _it) : node(_node), it(_it) {}

				inline bool is_end() const { return !node; }

				bool contains(T const query) const
				{
					if (node)
					{
						center_t const& center = node->center;
						if (!center.is_empty())
						{
							return (*it)->interval.contains(query, boundary_types::CLOSED);
						}
					}
					return false;	// fall-through to false
				}

				// move the position to the next available interval that might contain the query (jumps nodes if necessary)
				void advance(T const query)
				{
					if (node)
					{
						center_t const& center = node->center;
						if (query <= center.pivot)	// check if we need to jump nodes
						{
							// if any of the following are true, we jump nodes
							//     1. this iterator is the end (checks the edge case where we constructed a position that points to an empty node)
							//     2. the iterator points to a range that does not contain the query
							//     3. the incremented iterator is the end
							if (it == center.lesser.end() || query < (*it)->interval.a || ++it == center.lesser.end())
							{
								jump(query);
							}
						}
						else
						{
							// if any of the following are true, we jump nodes
							//     1. this iterator is the end (checks the edge case where we constructed a position that points to an empty node)
							//     2. the iterator points to a range that does not contain the query
							//     3. the incremented iterator is the greater
							if (it == center.greater.end() || query > (*it)->interval.b || ++it == center.greater.end())
							{
								jump(query);
							}
						}
					}
				}

			private:

				// assign the iterator to the appropriate value (may call jump if there is no iterator to assign at the current node)
				void assign(T const query)
				{
					if (node)
					{
						center_t const& center = node->center;
						if (center.is_empty()) { jump(query); }		// if there are no intervals at this node, jump to the next
						else
						{
							std::vector<entry_ptr_t> const& sorted = (query <= center.pivot) ? center.lesser : center.greater;
							it = sorted.begin();
						}
					}
				}

				// jump to the next relevant node, then assign the iterator
				void jump(T const query)
				{
					if (node)
					{
						center_t const& center = node->center;
						if (query == center.pivot) { node = nullptr; }	// if the query is the pivot, no other nodes will contain it. set the iterator to end
						else if (query < center.pivot)					// if the query is less than the pivot, take the left child
						{
							node = node->left.get();
							assign(query);
						}
						else											// if the query is greater than the pivot, take the right child
						{
							node = node->right.get();
							assign(query);
						}
					}
				}

			};

			// iterator forward until one of the following conditions is true
			//      1. we are at the end
			//      2. the position points to an interval that contains the query point
			void slide()
			{
				while (!m_position.is_end() && !m_position.contains(m_query))
				{
					m_position.advance(m_query);
				}
			}

			query_iterator(position_t const& position, T const query) : m_position(position), m_query(query)
			{
				slide();
			}

			// unfortunately, we have to overload operator!= for range-based for loops to work. but this is NOT true equality
			inline bool operator==(query_iterator const& rhs) const { return m_position.is_end() && rhs.m_position.is_end(); }
			inline bool operator!=(query_iterator const& rhs) const { return !(*this == rhs); }

			inline entry_t const& operator*() { return **m_position.it; }

			inline query_iterator& operator++()
			{
				m_position.advance(m_query);	// advance once immediately
				slide();						// slide forward until we hit something that matches the query
				return *this;
			}

			inline query_iterator operator++(int)
			{
				query_iterator ret = *this;
				++(*this);
				return ret;
			}

		private:

			position_t m_position;
			T const m_query;

		};

	public:

		struct query_range
		{
			
			query_range(query_iterator begin, query_iterator end) : m_begin(begin), m_end(end) {}

			inline query_iterator begin() const { return m_begin; }
			inline query_iterator end() const { return m_end; }

		private:

			query_iterator m_begin;
			query_iterator m_end;
		
		};

	public:

		explicit interval_tree(std::vector<entry_t>&& entries) : m_entries(std::move(entries)), m_root(interval_tree::construct(factory_args(m_entries))) {}

		query_range find(T const query) const
		{
			static std::vector<entry_ptr_t> const s_flag;
			query_iterator end(query_iterator::position_t(nullptr, s_flag.end()), query);
			if (m_entries.empty()) { return query_range(end, end); }	// if there are no intervals, return an empty range
			else
			{
				center_t const& center = m_root->center;
				query_iterator::position_t::iterator it = (query <= center.pivot) ? center.lesser.cbegin() : center.greater.cbegin();
				query_iterator begin(query_iterator::position_t(m_root.get(), it), query);
				return query_range(begin, end);
			}
		}

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

		// TODO probably rewrite with an STL algorithm
		static std::vector<entry_ptr_t> pointers(std::vector<entry_t> const& entries)
		{
			std::vector<entry_ptr_t> ptrs;
			ptrs.reserve(entries.size());
			for (entry_t const& entry : entries) { ptrs.push_back(&entry); }
			return ptrs;
		}

		// TODO probably rewrite with an STL algorithm
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