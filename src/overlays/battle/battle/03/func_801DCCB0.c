#include "battle_03.h"

MATCH u32 func_801DCCB0(void) {
    u32 total;
    u32 i;
    u32 sum;
    u16 half;

    total = 0;
    i     = 0;
    if (g_BattlePartyCount != 0u) {
        do {
            total += g_BattlePartyBattlers[i & BYTE_MASK].stats.stats.defense;
            i = i + 1u;
        } while ((i & BYTE_MASK) < g_BattlePartyCount);
    }
    half = (u16)total;
    sum  = half / (s32)g_BattlePartyCount;
    return (sum + D_801EC2EE) >> 1u;
}
