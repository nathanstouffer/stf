#ifndef STF_DS_SLOT_MAP_HPP_HEADER_GUARD
#define STF_DS_SLOT_MAP_HPP_HEADER_GUARD

#include <utility>
#include <vector>

namespace stf::ds
{

template <typename T>
// TODO (stouff) maybe swappable or movable constraint?
class slot_map
{
public:
    struct pair
    {
        size_t key;
        T value;
    };

    size_t size() const { return m_size; }

    void clear()
    {
        m_size = 0;
        m_index.clear();
        m_pairs.clear();
    }

    void reserve(size_t const size)
    {
        // check against index because we can never reduce its capacity
        if (size > m_index.capacity())
        {
            m_index.reserve(size);
            m_pairs.reserve(size);
        }
    }

    size_t push(T const& value)
    {
        size_t i = m_size;
        if (i >= m_pairs.size()) // assign key and push back
        {
            size_t key = i;
            m_index.push_back(i);
            m_pairs.push_back({key, value});
            ++m_size;
            return key;
        }
        else // use the next available key and overwrite
        {
            pair& next = m_pairs[i];
            size_t key = next.key;
            next.value = value;
            m_index[key] = i;
            ++m_size;
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
        if (i >= m_size)
        {
            return;
        }

        size_t key_of_last = m_pairs[m_size - 1].key;
        if (key != key_of_last)
        {
            size_t i_of_last = m_index[key_of_last];
            using std::swap;
            swap(m_pairs[i], m_pairs[i_of_last]);
            swap(m_index[key], m_index[key_of_last]);
        }
        --m_size;
    }

    T const& operator[](size_t const key) const { return m_pairs[m_index[key]].value; }

    T& operator[](size_t const key) { return const_cast<T&>(static_cast<const slot_map&>(*this)[key]); }

    using iterator = typename std::vector<pair>::iterator;
    using const_iterator = typename std::vector<pair>::const_iterator;

    const_iterator begin() const { return m_pairs.begin(); }
    const_iterator end() const { return m_pairs.begin() + m_size; }

    iterator begin() { return m_pairs.begin(); }
    iterator end() { return m_pairs.begin() + m_size; }

    iterator find(size_t const key)
    {
        if (key < m_index.size())
        {
            size_t i = m_index[key];
            if (i < m_size)
            {
                return m_pairs.begin() + i;
            }
        }
        return end();
    }

    const_iterator find(size_t const key) const
    {
        if (key < m_index.size())
        {
            size_t i = m_index[key];
            if (i < m_size)
            {
                return m_pairs.begin() + i;
            }
        }
        return end();
    }

private:
    // indexed by the offset, this is the underlying data structure
    std::vector<pair> m_pairs;
    // stores the size of the utilizes portion of m_pairs
    size_t m_size = 0;
    // indexed by key, returns the index in the underlying data structure
    std::vector<size_t> m_index;
};

} // namespace stf::ds

#endif