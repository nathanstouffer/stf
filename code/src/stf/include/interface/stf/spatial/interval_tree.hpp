#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "stf/math/constants.hpp"
#include "stf/math/interval.hpp"

/**
 * @file interval_tree.hpp
 * @brief A file containing a class that implements an interval tree
 */

namespace stf::spatial
{

/**
 * @brief A class that stores key-value pairs of intervals and values for querying.
 *
 * Given a query number x, the intersecting intervals can be computed in O(log(n) + k) time where n
 * is the number of intervals and k is the number of intersecting intervals. Duplicate keys are
 * supported, they will just be returned separately with their associated values.
 *
 * @todo Allocate nodes in chunks instead of one-by-one
 * @tparam T Number type (eg float)
 * @tparam V The value type stored in the tree
 */
template <typename T, typename V>
class interval_tree
{
  public:
    /**
     * @brief Type alias for an interval
     */
    using interval_t = math::interval<T>;

    /**
     * @brief A struct to store entries in the tree
     */
    struct entry_t
    {
        /**
         * @brief The interval associated with this entry
         */
        interval_t interval;

        /**
         * @brief The value associated with this entry
         */
        V value;

        /**
         * @brief Construct an entry
         * @param [in] _interval
         * @param [in] _value
         */
        entry_t(interval_t const& _interval, V const& _value) : interval(_interval), value(_value)
        {
        }

        /**
         * @brief Compute whether or not two entries are equal
         * @param [in] rhs
         * @return Whether or not the two entries are equal
         */
        inline bool operator==(entry_t const& rhs) const
        {
            return interval == rhs.interval && value == rhs.value;
        }
    };

  private:
    using entry_ptr_t = entry_t const*;

    struct center_t
    {
        T pivot;

        // these two lists are the same set of intervals (all containing the pivot), just sorted
        // differently
        std::vector<entry_ptr_t> lesser;  // sorted by begin point (ascending)
        std::vector<entry_ptr_t> greater; // sorted by end point (descending)

        center_t(T const _pivot) : pivot(_pivot) {}

        inline bool is_empty() const { return lesser.empty(); }

        void insert(entry_ptr_t entry)
        {
            lesser.push_back(entry);
            greater.push_back(entry);
        }

        void sort()
        {
            std::sort(lesser.begin(), lesser.end(), [](entry_ptr_t lhs, entry_ptr_t rhs)
                      { return lhs->interval.a < rhs->interval.a; });
            std::sort(greater.begin(), greater.end(), [](entry_ptr_t lhs, entry_ptr_t rhs)
                      { return lhs->interval.b > rhs->interval.b; });
        }
    };

    struct node_t
    {

        center_t center;

        // left and right subtrees
        std::unique_ptr<node_t> left;
        std::unique_ptr<node_t> right;

        node_t(center_t&& center, std::unique_ptr<node_t> left, std::unique_ptr<node_t> right)
            : center(std::move(center))
            , left(std::move(left))
            , right(std::move(right))
        {
        }

        inline bool has_left() const { return left; }
        inline bool has_right() const { return right; }
    };

  public:
    /**
     * @brief An iterator pointing to an underlying entry that also knows how to jump to the next
     * entry that contains a query point
     */
    struct query_iterator
    {
      public:
        /**
         * @brief Compute whether or not both iterators are the end
         * @param [in] rhs
         * @note Unfortunately, we have to overload the appropriate operators for range-based for
         * loops to work. This is NOT true equality
         * @return Whether or not both iterators are the end
         */
        inline bool operator==(query_iterator const& rhs) const
        {
            return m_position.is_end() && rhs.m_position.is_end();
        }

        /**
         * @brief Compute whether or not both iterators are not the end
         * @param [in] rhs
         * @note Unfortunately, we have to overload the appropriate operators for range-based for
         * loops to work. This is NOT true inequality
         * @return Whether or not either iterator is not the end
         */
        inline bool operator!=(query_iterator const& rhs) const { return !(*this == rhs); }

        /**
         * @brief Dereference the iterator
         * @return A const reference to underlying entry
         */
        inline entry_t const& operator*() { return **m_position.it; }

        /**
         * @brief Pre-increment the iterator
         * @return A reference to @p this after incrementing
         */
        inline query_iterator& operator++()
        {
            m_position.advance(m_query); // advance once immediately
            slide(); // slide forward until we hit something that matches the query
            return *this;
        }

        /**
         * @brief Post-increment the iterator
         * @return An incremented copy of @p this
         */
        inline query_iterator operator++(int)
        {
            query_iterator ret = *this;
            ++(*this);
            return ret;
        }

      private:
        friend class interval_tree;

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
                        return (*it)->interval.contains(query, boundary_types::closed);
                    }
                }
                return false; // fall-through to false
            }

            // move the position to the next available interval that might contain the query (jumps
            // nodes if necessary)
            void advance(T const query)
            {
                if (node)
                {
                    center_t const& center = node->center;
                    if (query <= center.pivot) // check if we need to jump nodes
                    {
                        // if any of the following are true, we jump nodes
                        //     1. this iterator is the end (checks the edge case where we
                        //     constructed a position that points to an empty node)
                        //     2. the iterator points to a range that does not contain the query
                        //     3. the incremented iterator is the end
                        if (it == center.lesser.end() || query < (*it)->interval.a ||
                            ++it == center.lesser.end())
                        {
                            jump(query);
                        }
                    }
                    else
                    {
                        // if any of the following are true, we jump nodes
                        //     1. this iterator is the end (checks the edge case where we
                        //     constructed a position that points to an empty node)
                        //     2. the iterator points to a range that does not contain the query
                        //     3. the incremented iterator is the greater
                        if (it == center.greater.end() || query > (*it)->interval.b ||
                            ++it == center.greater.end())
                        {
                            jump(query);
                        }
                    }
                }
            }

          private:
            // assign the iterator to the appropriate value (may call jump if there is no iterator
            // to assign at the current node)
            void assign(T const query)
            {
                if (node)
                {
                    center_t const& center = node->center;
                    if (center.is_empty())
                    {
                        jump(query);
                    } // if there are no intervals at this node, jump to the next
                    else
                    {
                        std::vector<entry_ptr_t> const& sorted =
                            (query <= center.pivot) ? center.lesser : center.greater;
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
                    if (query == center.pivot)
                    {
                        node = nullptr;
                    } // if the query is the pivot, no other nodes will contain it. set the iterator
                      // to end
                    else if (query <
                             center
                                 .pivot) // if the query is less than the pivot, take the left child
                    {
                        node = node->left.get();
                        assign(query);
                    }
                    else // if the query is greater than the pivot, take the right child
                    {
                        node = node->right.get();
                        assign(query);
                    }
                }
            }
        };

        // iterate forward until one of the following conditions is true
        //      1. we are at the end
        //      2. the position points to an interval that contains the query point
        void slide()
        {
            while (!m_position.is_end() && !m_position.contains(m_query))
            {
                m_position.advance(m_query);
            }
        }

        query_iterator(position_t const& position, T const query)
            : m_position(position)
            , m_query(query)
        {
            slide();
        }

      private:
        position_t m_position;
        T const m_query;
    };

    /**
     * @brief A range returned from a query
     */
    struct query_range
    {

        /**
         * @brief Construct a from a paair of iterators
         * @param [in] begin
         * @param [in] end
         */
        query_range(query_iterator begin, query_iterator end) : m_begin(begin), m_end(end) {}

        /**
         * @brief Return the beginning of the range
         * @return The beginning of the range
         */
        inline query_iterator begin() const { return m_begin; }

        /**
         * @brief Return the end of the range
         * @return The end of the range
         */
        inline query_iterator end() const { return m_end; }

      private:
        query_iterator m_begin;
        query_iterator m_end;
    };

  public:
    /**
     * @brief Construct an interval tree from a set of entries
     * @param [in] entries The entries that will be copied into the tree
     */
    explicit interval_tree(std::vector<entry_t> const& entries)
        : m_entries(entries)
        , m_root(interval_tree::construct(factory_args(m_entries)))
    {
    }

    /**
     * @brief Construct an interval tree from a set of entries
     * @param [in] entries The entries that will be moved into the tree
     */
    explicit interval_tree(std::vector<entry_t>&& entries)
        : m_entries(std::move(entries))
        , m_root(interval_tree::construct(factory_args(m_entries)))
    {
    }

    /**
     * @brief Copy constructor for interval_tree
     * @param [in] rhs The interval_tree to be copied
     */
    interval_tree(interval_tree const& rhs)
        : m_entries(rhs.m_entries)
        , m_root(interval_tree::construct(factory_args(m_entries)))
    {
    }

    /**
     * @brief Copy assignment operator for interval_tree
     * @param [in] rhs The interval_tree to be copied
     * @return A reference to the calling object
     */
    interval_tree& operator=(interval_tree const& rhs)
    {
        m_entries = rhs.m_entries;
        m_root = interval_tree::construct(factory_args(m_entries));
        m_end_flag = rhs.m_end_flag;
        return *this;
    }

    /**
     * @brief Move constructor for interval_tree
     * @param [in] rhs The interval_tree to be moved
     */
    interval_tree(interval_tree&& rhs) noexcept = default;

    /**
     * @brief Move assignment operator for interval_tree
     * @param [in] rhs The interval_tree to be copied
     * @return A reference to the calling object
     */
    interval_tree& operator=(interval_tree&& rhs) noexcept = default;

    /**
     * @brief Find a range of entries whose intervals contain a query point
     * @param [in] query The query value
     * @return The range of entries that contain @p query
     */
    query_range find(T const query) const
    {
        using position_t = typename query_iterator::position_t;
        using iterator_t = typename position_t::iterator;

        query_iterator end(position_t(nullptr, m_end_flag.end()), query);
        if (m_entries.empty())
        {
            return query_range(end, end);
        } // if there are no intervals, return an empty range
        else
        {
            center_t const& center = m_root->center;
            iterator_t it =
                (query <= center.pivot) ? center.lesser.cbegin() : center.greater.cbegin();
            query_iterator begin(position_t(m_root.get(), it), query);
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
        factory_args(std::vector<entry_t> const& entries)
            : intervals(interval_tree::pointers(entries))
            , sorted(interval_tree::sorted(entries))
        {
        }
    };

    static std::unique_ptr<node_t> construct(factory_args const& args)
    {
        // base case where there are no intervals
        if (args.intervals.empty())
        {
            return nullptr;
        }

        // args.sorted.size() will always be even because it will have exactly 2 *
        // args.intervals.size() elements -- two endpoints per interval
        size_t mid = args.sorted.size() / 2;
        T median = math::constants<T>::half * (args.sorted[mid - 1].x + args.sorted[mid].x);

        factory_args left{};
        factory_args right{};
        center_t center(median);

        // iterate over intervals, adding to the appropriate node
        for (entry_ptr_t entry : args.intervals)
        {
            if (entry->interval.b < center.pivot)
            {
                left.intervals.push_back(entry);
            } // interval is entirely to the left
            else if (center.pivot < entry->interval.a)
            {
                right.intervals.push_back(entry);
            } // interval is entirely to the right
            else
            {
                center.insert(entry);
            } // invterval contains the pivot
        }

        // iterate over sorted points, adding to the appropriate node
        for (sortable_t sortable : args.sorted)
        {
            if (sortable.entry->interval.b < center.pivot)
            {
                left.sorted.push_back(sortable);
            } // interval is entirely to the left
            else if (center.pivot < sortable.entry->interval.a)
            {
                right.sorted.push_back(sortable);
            } // interval is entirely to the right
        }

        center.sort(); // sort the intervals that contain the pivot

        return std::make_unique<node_t>(std::move(center), interval_tree::construct(left),
                                        interval_tree::construct(right));
    }

    // TODO probably rewrite with an STL algorithm
    static std::vector<entry_ptr_t> pointers(std::vector<entry_t> const& entries)
    {
        std::vector<entry_ptr_t> ptrs;
        ptrs.reserve(entries.size());
        for (entry_t const& entry : entries)
        {
            ptrs.push_back(&entry);
        }
        return ptrs;
    }

    // TODO probably rewrite with an STL algorithm
    static std::vector<sortable_t> sorted(std::vector<entry_t> const& entries)
    {
        std::vector<sortable_t> sortable;
        sortable.reserve(2 * entries.size());
        for (entry_t const& entry : entries)
        {
            sortable.push_back(sortable_t(entry.interval.a, &entry));
            sortable.push_back(sortable_t(entry.interval.b, &entry));
        }
        std::sort(sortable.begin(), sortable.end(),
                  [](sortable_t const& lhs, sortable_t const& rhs) { return lhs.x < rhs.x; });
        return sortable;
    }

  private:
    std::vector<entry_t> m_entries;
    std::unique_ptr<node_t> m_root;
    std::vector<entry_ptr_t> m_end_flag;
};

} // namespace stf::spatial