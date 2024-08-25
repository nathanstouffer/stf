#pragma once

#include <list>
#include <unordered_map>

/**
 * @file indexed_list.hpp
 * @brief A file containing a class that implements a list with an index overlaid on top for access via a key
 */

namespace stf::ds
{

	template<typename key_t, typename entry_t>
	class indexed_list final
	{
	public:

		struct pair_t
		{
			key_t key;
			entry_t entry;
		};

	private:

		using list_t = std::list<pair_t>;
		using list_iterator = typename list_t::iterator;
		using list_const_iterator = typename list_t::const_iterator;

		using map_t = std::unordered_map<key_t, list_iterator>;
		using map_iterator = typename map_t::iterator;
		using map_const_iterator = typename map_t::const_iterator;

		list_t m_list;
		map_t m_index;

	public:

		using iterator = list_iterator;
		using const_iterator = list_const_iterator;

	public:

		inline size_t size() const { return m_index.size(); }
		inline bool is_empty() const { return m_index.empty(); }

		void clear()
		{
			m_index.clear();
			m_list.clear();
		}

		const_iterator find(key_t const& key) const
		{
			map_const_iterator it = m_index.find(key);
			return (it != m_index.end()) ? it->second : m_list.end();
		}

		iterator find(key_t const& key) const
		{
			map_iterator it = m_index.find(key);
			return (it != m_index.end()) ? it->second : m_list.end();
		}

		inline bool contains(key_t const& key) const
		{
			return m_index.find(key) != m_index.end();
		}

		inline pair_t const& at(key_t const& key) const { return *m_index.at(key); }
		inline pair_t& at(key_t const& key) { return *m_index.at(key); }

		inline void erase(const_iterator it)
		{
			m_index.erase(it->key);
			m_list.erase(it);
		}

		void erase(key_t const& key)
		{
			list_const_iterator it = find(key);
			if (it != m_list.end())
			{
				erase(it);
			}
		}

		inline const_iterator replace(key_t const& key, entry_t entry)
		{
			iterator it = m_index.at(key);
			pair_t& pair = *it;
			pair.entry = std::move(entry);
			return it;
		}

		// moves it to the specified position in the list
		inline void splice(const_iterator pos, const_iterator it)
		{
			m_list.splice(post, m_list, it);
		}

		inline void splice(const_iterator pos, key_t const& key)
		{
			map_const_iterator found = m_index.find(key);
			if (found != m_index.end())
			{
				const_iterator it = found->second;
				splice(pos, it);
			}
		}

		inline iterator insert(const_iterator pos, key_t const& key, entry_t entry)
		{
			map_iterator found = m_index.find(key);
			if (found != m_index.end())
			{
				m_list.erase(found->second);
				list_iterator inserted = m_list.insert(pos, { key, std::move(entry) });
				found->second = inserted;
				return inserted;
			}
			else
			{
				list_iterator inserted = m_list.insert(pos, { key, std::move(entry) });
				m_index[key] = inserted;
				return inserted;
			}
		}

		iterator touch_to_front(iterator it)
		{
			if (it != m_list.end())
			{
				splice(begin(), it);
			}
		}

		inline iterator touch_to_front(key_t const& key) { return touch_to_front(find(key)); }

		iterator touch_to_back(iterator it)
		{
			if (it != m_list.end())
			{
				splice(end(), it);
			}
		}

		inline iterator touch_to_back(key_t const& key) { return touch_to_back(find(key)); }

		inline void push_front(key_t const& key, entry_t entry)
		{
			insert(m_list.begin(), key, std::move(entry));
		}

		inline void push_back(key_t const& key, entry_t entry)
		{
			insert(m_list.end(), key, std::move(entry));
		}

		inline void pop_front()
		{
			m_index.erase(m_list.front().key);
			m_list.pop_front();
		}

		inline void pop_back()
		{
			m_index.erase(m_list.back().key());
			m_list.pop_back();
		}

		inline pair_t const& front() const { return m_list.front(); }
		inline pair_t&       front()       { return m_list.front(); }
		
		inline pair_t const& back() const { return m_list.back(); }
		inline pair_t&       back()       { return m_list.back(); }

		const_iterator begin() const { return m_list.begin(); }
		const_iterator end()   const { return m_list.end(); }

		iterator begin() const { return m_list.begin(); }
		iterator end()   const { return m_list.end(); }

	};

}