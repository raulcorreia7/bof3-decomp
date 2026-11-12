#include "boss025_13.h"

MATCH void func_800C2184(void) {
    u16  hp;
    u16  max_hp;
    u16  ap;
    u16  max_ap;
    u16* hp_cell;

    g_Battle.choose_ending_hook = func_800C2634;
    g_Battle.end_hook           = func_800C2680;
    g_Battle.boss_event_hook    = func_800C2208;
    g_Battle.outcome.surprise   = 3;

    hp_cell = &g_BattlePartyBattlers[0].chr.hp;
    hp      = *hp_cell;
    max_hp  = g_BattlePartyBattlers[0].chr.stats.max_hp;
    ap      = g_BattlePartyBattlers[0].chr.ap;
    max_ap  = g_BattlePartyBattlers[0].chr.stats.max_ap;

    D_800C32B4    = hp;
    *hp_cell      = max_hp;
    D_800C32B8    = ap;
    D_80145F1A[0] = max_ap;
}
