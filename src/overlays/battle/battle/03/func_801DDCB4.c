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
    FAKE_REG(u32, enemy_index, "v0");

    id = battler_index & BYTE_MASK;
    if (id < 3u) {
        counter = g_Game.members[id].u.turn.counter & BYTE_MASK;
    } else {
        counter = ENEMY_COMBATANT(id).turn.counter & BYTE_MASK;
    }
    if (counter == 0u) {
        return 0u;
    }

    r100 = RANDOM_PERCENT();
    if (counter < 3u ? (s_BattleStatusRecoveryChances[counter] >= r100) : (r100 < 76)) {
        return 1u;
    }

    rt  = s_BattleStatusRecoveryPenalties;
    id2 = battler_index & BYTE_MASK;
    if (id2 < 3u) {
        state = g_Game.members[id2].chr.stats.resistances[RES_INDEX_STATUS];
    } else {
        enemy_index = id2 - 3u;
        state       = g_BattleEnemyBattlers[enemy_index].stats.resistances[RES_INDEX_STATUS];
    }

    limit = 10000 - rt[state] * 50;
    return (RANDOM_MOD(10000) <= limit) ? 1u : 0u;
}
