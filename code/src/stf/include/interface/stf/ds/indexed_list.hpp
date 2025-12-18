#pragma once

#include <list>
#include <unordered_map>

/**
 * @file indexed_list.hpp
 * @brief A file containing a class that implements a list with an index overlaid on top for access
 * via a key
 */

namespace stf::ds
{

/**
 * @brief A class that stores a list with an overlaid index for quick access for a key
 * @tparam key_t The type of the key that is used to index the list
 * @tparam entry_t The type of the entry that is stored in the list
 * @note key_t must have a hash function defined that is compatible with std::unordered_map
 * @note entry_t must have a correct move constructor
 */
template <typename key_t, typename entry_t>
class indexed_list final
{
  public:
    /**
     * @brief A struct to represent the items stored in indexed_list
     */
    struct element_t
    {
        /**
         * @brief The key of the element
         */
        key_t key;

        /**
         * @brief The entry stored in the element
         */
        entry_t entry;
    };

  private:
    using list_t = std::list<element_t>;
    using list_iterator = typename list_t::iterator;
    using list_const_iterator = typename list_t::const_iterator;

    using map_t = std::unordered_map<key_t, list_iterator>;
    using map_iterator = typename map_t::iterator;
    using map_const_iterator = typename map_t::const_iterator;

    list_t m_list;
    map_t m_index;

  public:
    /**
     * @brief Iterator exposed for element access
     */
    using iterator = list_iterator;

    /**
     * @brief Read-only iterator exposed for element access
     */
    using const_iterator = list_const_iterator;

  public:
    /**
     * @brief Compute the number of elements in the list
     * @return The number of elements in the list
     */
    inline size_t size() const { return m_index.size(); }

    /**
     * @brief Compute whether or not the list is empty
     * @return Whether or not the list is empty
     */
    inline bool is_empty() const { return m_index.empty(); }

    /**
     * @brief Clear all elements in the list
     */
    void clear()
    {
        m_index.clear();
        m_list.clear();
    }

    /**
     * @brief Find a particular element in the list
     * @param [in] key The search key
     * @return A const iterator to the element
     */
    const_iterator find(key_t const& key) const
    {
        map_const_iterator it = m_index.find(key);
        return (it != m_index.end()) ? it->second : m_list.end();
    }

    /**
     * @brief Find a particular element in the list
     * @param [in] key The search key
     * @return An iterator to the element
     */
    iterator find(key_t const& key)
    {
        map_iterator it = m_index.find(key);
        return (it != m_index.end()) ? it->second : m_list.end();
    }

    /**
     * @brief Compute whether or not a particular key is present in the list
     * @param [in] key The search key
     * @return Whether or not the key is present
     */
    inline bool contains(key_t const& key) const { return m_index.find(key) != m_index.end(); }

    /**
     * @brief Access the element at a particular key
     * @param [in] key The search key
     * @return A const reference to the element
     */
    inline element_t const& at(key_t const& key) const { return *m_index.at(key); }

    /**
     * @brief Access the element at a particular key
     * @param [in] key The search key
     * @return A reference to the element
     */
    inline element_t& at(key_t const& key) { return *m_index.at(key); }

    /**
     * @brief Erase an element of the list
     * @param [in] it An iterator pointing to the element to be erased
     */
    inline void erase(const_iterator it)
    {
        m_index.erase(it->key);
        m_list.erase(it);
    }

    /**
     * @brief Erase an element of the list
     * @param [in] key The key of the element that is to be erased
     */
    void erase(key_t const& key)
    {
        list_const_iterator it = find(key);
        if (it != m_list.end())
        {
            erase(it);
        }
    }

    /**
     * @brief Replace the entry at a key in the list
     * @param [in] key The key of the element
     * @param [in] entry The new value of the entry
     * @return A const iterator to the element
     */
    inline const_iterator replace(key_t const& key, entry_t entry)
    {
        iterator it = m_index.at(key);
        element_t& element = *it;
        element.entry = std::move(entry);
        return it;
    }

    // moves it to the specified position in the list

    /**
     * @brief Move an element of the list to a new position
     * @param [in] pos The destination position in the list
     * @param [in] it The iterator that is to be moved
     * @note @p it is placed directly preceding @p pos
     */
    inline void splice(const_iterator pos, const_iterator it) { m_list.splice(pos, m_list, it); }

    /**
     * @brief Move an element of the list to a new position
     * @param [in] pos The destination position in the list
     * @param [in] key The key of the element that is to be moved
     * @note @p it is placed directly preceding @p pos
     */
    void splice(const_iterator pos, key_t const& key)
    {
        map_const_iterator found = m_index.find(key);
        if (found != m_index.end())
        {
            const_iterator it = found->second;
            splice(pos, it);
        }
    }

    /**
     * @brief Write an element to the list
     * @param [in] pos The position at which to insert the element
     * @param [in] key The key to store the element
     * @param [in] entry The entry that is to be stored
     * @return An iterator to the inserted element
     * @note The element is placed directly preceding @p pos
     */
    iterator insert_or_assign(const_iterator pos, key_t const& key, entry_t entry)
    {
        map_iterator found = m_index.find(key);
        if (found != m_index.end())
        {
            m_list.erase(found->second);
            list_iterator inserted = m_list.insert(pos, {key, std::move(entry)});
            found->second = inserted;
            return inserted;
        }
        else
        {
            list_iterator inserted = m_list.insert(pos, {key, std::move(entry)});
            m_index[key] = inserted;
            return inserted;
        }
    }

    /**
     * @brief Move an element to the front of the list
     * @param [in] it An iterator pointing to the element that is to be moved
     * @return An iterator pointing to the moved element
     */
    iterator move_to_front(iterator it)
    {
        if (it != m_list.end())
        {
            splice(begin(), it);
        }
        return it;
    }

    /**
     * @brief Move an element to the front of the list
     * @param [in] key The key of the element that is to be moved
     * @return An iterator pointing to the moved element
     */
    inline iterator move_to_front(key_t const& key) { return move_to_front(find(key)); }

    /**
     * @brief Move an element to the back of the list
     * @param [in] it An iterator pointing to the element that is to be moved
     * @return An iterator pointing to the moved element
     */
    iterator move_to_back(iterator it)
    {
        if (it != m_list.end())
        {
            splice(end(), it);
        }
        return it;
    }

    /**
     * @brief Move an element to the back of the list
     * @param [in] key The key of the element that is to be moved
     * @return An iterator pointing to the moved element
     */
    inline iterator move_to_back(key_t const& key) { return move_to_back(find(key)); }

    /**
     * @brief Push an element to the front of the list
     * @param [in] key The key of the element
     * @param [in] entry The entry to be stored
     */
    inline void push_front(key_t const& key, entry_t entry)
    {
        insert_or_assign(m_list.begin(), key, std::move(entry));
    }

    /**
     * @brief Push an element to the back of the list
     * @param [in] key The key of the element
     * @param [in] entry The entry to be stored
     */
    inline void push_back(key_t const& key, entry_t entry)
    {
        insert_or_assign(m_list.end(), key, std::move(entry));
    }

    /**
     * @brief Pop the front of the list
     */
    inline void pop_front()
    {
        m_index.erase(m_list.front().key);
        m_list.pop_front();
    }

    /**
     * @brief Pop the back of the list
     */
    inline void pop_back()
    {
        m_index.erase(m_list.back().key());
        m_list.pop_back();
    }

    /**
     * @brief Access to the front of the list
     * @return A const reference to the front of the list
     */
    inline element_t const& front() const { return m_list.front(); }

    /**
     * @brief Access to the front of the list
     * @return A reference to the front of the list
     */
    inline element_t& front() { return m_list.front(); }

    /**
     * @brief Access to the back of the list
     * @return A const reference to the back of the list
     */
    inline element_t const& back() const { return m_list.back(); }

    /**
     * @brief Access to the back of the list
     * @return A reference to the back of the list
     */
    inline element_t& back() { return m_list.back(); }

    /**
     * @brief Access to the front of the list
     * @return A const iterator pointing to the front of the list
     */
    const_iterator begin() const { return m_list.begin(); }

    /**
     * @brief Access to the end of the list
     * @return A const iterator pointing to the end of the list
     */
    const_iterator end() const { return m_list.end(); }

    /**
     * @brief Access to the front of the list
     * @return An iterator pointing to the front of the list
     */
    iterator begin() { return m_list.begin(); }

    /**
     * @brief Access to the end of the list
     * @return An iterator pointing to the end of the list
     */
    iterator end() { return m_list.end(); }
};

} // namespace stf::ds