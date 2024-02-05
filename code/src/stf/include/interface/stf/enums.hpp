#pragma once

namespace stf
{

    enum class endpoints
    {
        CLOSED,
        OPEN
    };

    inline endpoints complement(endpoints input)
    {
        switch (input)
        {
            case endpoints::CLOSED: return endpoints::OPEN; break;
            case endpoints::OPEN: return endpoints::CLOSED; break;
            default: return endpoints::CLOSED;
        }
    }
    
} // stf