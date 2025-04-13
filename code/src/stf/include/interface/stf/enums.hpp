#pragma once

namespace stf
{

    /**
     * @brief An enum to specify the boundary type
     */
    enum class boundary_types : uint32_t
    {
        closed = 0x00000000,
        open   = 0xFFFFFFFF
    };

    /**
     * @brief Compute the complement of the boundary type
     * @param input [in]
     * @return The complement of @p input
     */
    inline boundary_types complement(boundary_types input)
    {
        uint32_t casted = static_cast<uint32_t>(input);
        return static_cast<boundary_types>(~casted);
    }
    
} // stf