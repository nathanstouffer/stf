#ifndef STF_DS_SLOT_MAP_HPP_HEADER_GUARD
#define STF_DS_SLOT_MAP_HPP_HEADER_GUARD

#include <vector>

namespace stf::ds
{

template <typename T>
// TODO (stouff) maybe swappable or movable constraint?
class slot_map
{
public:
    size_t size() const { return m_entries.size(); }

    void reserve(size_t const size)
    {
        m_offsets.reserve(size);
        m_ids.reserve(size);
        m_entries.reserve(size);
    }

    size_t push(T const& entry)
    {
        // insert to entries
        size_t offset = m_entries.size();
        m_entries.push_back(entry);

        // update indexing
        if (offset >= m_ids.size())
        {
            m_offsets.push_back(offset);
            m_ids.push_back(offset);
            return offset;
        }
        else
        {
            size_t id = m_ids[offset];
            m_offsets[id] = offset;
            return id;
        }
    }

    void erase(size_t const id)
    {
        // TODO (stouff) implement this
    }

    T const& operator[](size_t const id) const { return m_entries[m_offsets[id]]; }

    T& operator[](size_t const id) { return const_cast<T&>(static_cast<const slot_map&>(*this)[id]); }

private:
    std::vector<size_t> m_offsets;
    std::vector<size_t> m_ids;
    std::vector<T> m_entries;
};

} // namespace stf::ds

#endif