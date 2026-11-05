#include "battle_03.h"

/* Countdown/retry state bytes: per-battler fields viewed as arrays whose
 * element stride equals one battler record (0x140 local, 0x118 enemy).
 * D_801EAFFC holds short-counter thresholds; D_801EAFF4 maps a retry-state
 * byte to the retry percentage used for the long-shot reroll below. */

MATCH u8 func_801DDCB4(u32 battler_index) {
    u32 id;
    u32 id2;
    u8  counter;
    u8  state;
    s32 limit;
    s32 r100;
    u8* rt;
    /* FAKE: retail keeps the enemy row index in v0 and scales it in v1. */
    MATCH_REG(u32, enemy_index, "v0");

    id = battler_index & BYTE_MASK;
    if (id < 3u) {
        counter = g_BattlePartyBattlers[id].counter_121 & BYTE_MASK;
    } else {
        counter = ENEMY_COMBATANT(id).unk_FD & BYTE_MASK;
    }
    if (counter == 0u) {
        return 0u;
    }

    r100 = rand() % 100;
    if (counter < 3u ? ((s32)s_BattleStatusRecoveryChances[counter] >= r100) : (r100 < 76)) {
        return 1u;
    }

    rt  = s_BattleStatusRecoveryPenalties;
    id2 = battler_index & BYTE_MASK;
    if (id2 < 3u) {
        state = g_BattlePartyBattlers[id2].chr.stats.resistances[RES_SLOT_STATUS];
    } else {
        enemy_index = id2 - 3u;
        state       = D_801EB630[enemy_index].stats.resistances[RES_SLOT_STATUS];
    }

    limit = 10000 - (s32)rt[state] * 50;
    return (rand() % 10000 <= limit) ? 1u : 0u;
}
