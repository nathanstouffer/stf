#pragma once

namespace stf
{

    enum class boundary : uint32_t
    {
        CLOSED = 0x00000000,
        OPEN   = 0xFFFFFFFF
    };

    inline boundary complement(boundary input)
    {
        uint32_t casted = static_cast<uint32_t>(input);
        return static_cast<boundary>(~casted);
    }
    
} // stf