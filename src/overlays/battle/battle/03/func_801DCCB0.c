#include "battle_03.h"

MATCH u32 func_801DCCB0(void) {
    u32 total;
    u32 i;
    u32 sum;
    u16 half;

    total = 0;
    i     = 0;
    if (g_Battle.party_count != 0u) {
        do {
            total += g_Game.members[i & BYTE_MASK].chr.stats.defense;
            i = i + 1u;
        } while ((i & BYTE_MASK) < g_Battle.party_count);
    }
    half = total;
    sum  = half / g_Battle.party_count;
    return (sum + D_801EC2EE) >> 1u;
}
