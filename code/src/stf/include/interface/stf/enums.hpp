#pragma once

namespace stf
{

    enum class boundary_types : uint32_t
    {
        CLOSED = 0x00000000,
        OPEN   = 0xFFFFFFFF
    };

    inline boundary_types complement(boundary_types input)
    {
        uint32_t casted = static_cast<uint32_t>(input);
        return static_cast<boundary_types>(~casted);
    }
    
} // stf