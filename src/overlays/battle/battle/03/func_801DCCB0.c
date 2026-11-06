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
            total += g_BattlePartyBattlers[i & 0xFF].chr.stats.defense;
            i = i + 1u;
        } while ((i & 0xFF) < g_BattlePartyCount);
    }
    half = total;
    sum  = half / g_BattlePartyCount;
    return (sum + D_801EC2EE) >> 1u;
}
