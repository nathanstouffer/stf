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
        if (size() == 0 || id >= m_offsets.size())
        {
            return;
        }

        size_t offset = m_offsets[id];
        if (offset >= m_entries.size())
        {
            return;
        }

        size_t last_id = m_ids[m_entries.size() - 1];
        size_t last_offset = m_offsets[last_id];
        using std::swap;
        swap(m_ids[offset], m_ids[last_offset]);
        swap(m_entries[offset], m_entries[last_offset]);
        swap(m_offsets[id], m_offsets[last_id]);
        m_entries.pop_back();
    }

    // TODO (stouff) set up iterators
    // TODO (stouff) set up find

    T const& operator[](size_t const id) const { return m_entries[m_offsets[id]]; }

    T& operator[](size_t const id) { return const_cast<T&>(static_cast<const slot_map&>(*this)[id]); }

private:
    std::vector<size_t> m_offsets;
    std::vector<size_t> m_ids;
    std::vector<T> m_entries;
};

} // namespace stf::ds

#endif