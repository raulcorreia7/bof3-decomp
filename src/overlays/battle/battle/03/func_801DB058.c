#include "battle_03.h"

/* computes average/max thresholds for eligible enemy and local
 * battlers, then marks the battlers that pass each threshold pair with the
 * shared `0x8000` state bit.
 */
MATCH u8 func_801DB058(void) {
    u16 local_hits;
    u16 total;
    u16 maximum;
    u8  count;
    u32 index;

    local_hits = 0u;
    total      = 0u;
    maximum    = 0u;
    count      = 0u;
    index      = 3u;
    while ((u8)index < 11u) {
        if (func_801DB2F8((u8)index) != 0u) {
            u32 slot;
            u16 value;

            slot  = (u8)index - 3u;
            value = g_BattleEnemyBattlers[slot].stats.agility;
            total += value;
            CLAMP_MIN(maximum, value);
            count += 1u;
        }
        index += 1u;
    }

    if (total != 0u) {
        total = total / count;
    }

    count = 0u;
    index = 0u;
    while ((u8)index < 3u) {
        if ((func_801DB9E4((u8)index) != 0u) && (func_801DB3A0((u8)index, total, maximum) != 0u)) {
            g_Game.members[(u8)index].u.turn.action_flags.value |= COMBATANT_FLAG_PREEMPTIVE_TURN;
            count += 1u;
        }
        index += 1u;
    }

    if (count != 0u) {
        local_hits += 1u;
    }

    total   = 0u;
    maximum = 0u;
    count   = 0u;
    index   = 0u;
    while ((u8)index < 3u) {
        if (func_801DB2F8((u8)index) != 0u) {
            u16 value;

            value = g_Game.members[(u8)index].chr.stats.agility;
            total += value;
            CLAMP_MIN(maximum, value);
            count += 1u;
        }
        index += 1u;
    }

    if (total != 0u) {
        total = total / count;
    }

    index = 3u;
    while ((u8)index < 11u) {
        if ((func_801DB9E4((u8)index) != 0u) && (func_801DB3E4((u8)index, total, maximum) != 0u)) {
            u32 slot;

            slot = (u8)index - 3u;
            g_BattleEnemyBattlers[slot].turn.action_flags.value |= COMBATANT_FLAG_PREEMPTIVE_TURN;
        }
        index += 1u;
    }

    return local_hits;
}
