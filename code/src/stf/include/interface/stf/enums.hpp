#pragma once

namespace stf
{

    enum class boundary
    {
        CLOSED,
        OPEN
    };

    inline boundary complement(boundary input)
    {
        switch (input)
        {
            case boundary::CLOSED: return boundary::OPEN; break;
            case boundary::OPEN: return boundary::CLOSED; break;
            default: return boundary::CLOSED;
        }
    }
    
} // stf