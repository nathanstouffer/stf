#ifndef STF_DS_SLOT_MAP_HPP_HEADER_GUARD
#define STF_DS_SLOT_MAP_HPP_HEADER_GUARD

#include <concepts>
#include <utility>
#include <vector>

namespace stf::ds
{

template <std::swappable T>
class slot_map
{
public:

    size_t size() const { return m_values.size(); }

    void clear()
    {
        m_index.clear();
        m_keys.clear();
        m_values.clear();
    }

    void reserve(size_t const size)
    {
        // check against index because we can never reduce its capacity
        if (size > m_index.capacity())
        {
            m_index.reserve(size);
            m_keys.reserve(size);
            m_values.reserve(size);
        }
    }

    size_t push(T const& value)
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

    T const& operator[](size_t const key) const { return m_values[m_index[key]]; }

    T& operator[](size_t const key) { return const_cast<T&>(static_cast<const slot_map&>(*this)[key]); }

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const { return m_values.begin(); }
    const_iterator end() const { return m_values.end(); }

    iterator begin() { return m_values.begin(); }
    iterator end() { return m_values.end(); }

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