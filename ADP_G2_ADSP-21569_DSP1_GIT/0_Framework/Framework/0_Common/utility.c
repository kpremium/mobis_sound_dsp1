#include "common.h"

uint32_t internal_to_system_address_translation(uint32_t nMemAddr)
{
    uint32_t result = nMemAddr;

    /* Address translation only applies to SHARC processors */

    /* IF (Supplied memory address is in L1) */
    if ((nMemAddr >= 0x00240000u) && (nMemAddr <= 0x0039FFFFu))
    {
        result = (nMemAddr | 0x28000000u);
    }
    /* ELSE (Supplied address could be L2 or L3) */
    else
    {
        result = nMemAddr;
    }

    return result;
}

uint32_t system_to_internal_address_translation(uint32_t nMemAddr)
{
    uint32_t result = nMemAddr;

    /* Address translation only applies to SHARC processors */

    /* IF (Supplied memory address is in L1) */
    if ((nMemAddr >= 0x28240000u) && (nMemAddr <= 0x2839FFFFu))
    {
        result = (nMemAddr & 0x3FFFFFu);
    }
    /* ELSE (Supplied address could be L2 or L3) */
    else
    {
        result = nMemAddr;
    }

    return result;
}

