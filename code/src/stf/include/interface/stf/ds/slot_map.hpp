#ifndef STF_DS_SLOT_MAP_HPP_HEADER_GUARD
#define STF_DS_SLOT_MAP_HPP_HEADER_GUARD

#include <concepts>
#include <utility>
#include <vector>

namespace stf::ds
{

/**
 * @brief A class for storing key-value pairs in contiguous memory
 * @tparam T Value type
 *
 * A map for storing key-value pairs in contiguous memory with O(1) insertions/deletions and stable identifiers. The
 * identifiers are stable but the order of the values in the underlying data structure may change.
 */
template <std::swappable T>
class slot_map
{
public:
    /**
     * @brief Return the number of elements in the map
     * @return The number of elements in the map
     */
    size_t size() const { return m_values.size(); }

    /**
     * @brief Clear the map
     */
    void clear()
    {
        m_index.clear();
        m_keys.clear();
        m_values.clear();
    }

    /**
     * @brief Reserve contiguous memory blocks
     * @param [in] capacity The number of values to reserve for
     */
    void reserve(size_t const capacity)
    {
        // check against index because we can never reduce its capacity
        if (capacity > m_index.capacity())
        {
            m_index.reserve(capacity);
            m_keys.reserve(capacity);
            m_values.reserve(size);
        }
    }

    /**
     * @brief Insert a value into the map
     * @param [in] value The value to insert
     * @return The id that can be used to access the inserted value
     */
    size_t insert(T const& value)
    {
        size_t i = m_values.size();
        if (i >= m_keys.size()) // assign key and push back
        {
            size_t key = i;
            m_index.push_back(i);
            m_keys.push_back(key);
            m_values.push_back(value);
            return key;
        }
        else // use the next available key and overwrite
        {
            size_t key = m_keys[i];
            m_index[key] = i;
            m_values[i] = value;
            return key;
        }
    }

    /**
     * @brief Erase a key from the map
     * @param [in] key The key to erase
     */
    void erase(size_t const key)
    {
        if (size() == 0 || key >= m_index.size())
        {
            return;
        }

        size_t i = m_index[key];
        if (i >= m_values.size())
        {
            return;
        }

        size_t i_of_last = m_values.size() - 1;
        size_t key_of_last = m_keys[i_of_last];
        if (key != key_of_last)
        {
            using std::swap;
            swap(m_index[key], m_index[key_of_last]);
            swap(m_keys[i], m_keys[i_of_last]);
            swap(m_values[i], m_values[i_of_last]);
        }
        m_values.pop_back();
    }

    /**
     * @brief Access a specific value of the map
     * @param [in] key The key to access
     * @return A const reference to the value
     */
    T const& operator[](size_t const key) const { return m_values[m_index[key]]; }

    /**
     * @brief Access a specific value of the map
     * @param [in] key The key to access
     * @return A reference to the value
     */
    T& operator[](size_t const key) { return const_cast<T&>(static_cast<const slot_map&>(*this)[key]); }

    /**
     * @brief iterator type alias
     */
    using iterator = typename std::vector<T>::iterator;

    /**
     * @brief const iterator type alias
     */
    using const_iterator = typename std::vector<T>::const_iterator;

    /**
     * @brief Return the begin iterator
     * @return The begin iterator
     */
    const_iterator begin() const { return m_values.begin(); }

    /**
     * @brief Return the end iterator
     * @return The end iterator
     */
    const_iterator end() const { return m_values.end(); }

    /**
     * @brief Return the begin iterator
     * @return The begin iterator
     */
    iterator begin() { return m_values.begin(); }

    /**
     * @brief Return the end iterator
     * @return The end iterator
     */
    iterator end() { return m_values.end(); }

    /**
     * @brief Find an element in the map
     * @param [in] key The search key
     * @return Iterator holding the value or end if the key is not present
     */
    iterator find(size_t const key)
    {
        if (key < m_index.size())
        {
            size_t i = m_index[key];
            if (i < m_values.size())
            {
                return m_values.begin() + i;
            }
        }
        return end();
    }

    /**
     * @brief Find an element in the map
     * @param [in] key The search key
     * @return Iterator holding the value or end if the key is not present
     */
    const_iterator find(size_t const key) const
    {
        if (key < m_index.size())
        {
            size_t i = m_index[key];
            if (i < m_values.size())
            {
                return m_values.begin() + i;
            }
        }
        return end();
    }

private:
    // keyed by m_index, this is the underlying data structure
    std::vector<T> m_values;
    // back-pointers from m_values to m_index (indexed in parallel)
    std::vector<size_t> m_keys;
    // indexed by key, returns the index in the underlying data structure
    std::vector<size_t> m_index;
};

} // namespace stf::ds

#endif