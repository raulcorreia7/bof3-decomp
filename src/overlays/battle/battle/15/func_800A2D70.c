#include "battle_15.h"

/* Battler element rows: the resistance byte at +0x00 (func_800A30E8) is
 * followed by the element-slot bytes the 0x1C0 element mask selects. */

MATCH s16 func_800A2D70(u8 battler_index, u16 element_mask) {
    s32 value = 0;

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (element_mask & ELEM_PSIONIC) {
            value = D_800B494C[g_BattlePartyBattlers[battler_index].chr.stats.resistances[RES_INDEX_PSIONIC]];
        }
        if (element_mask & ELEM_STATUS) {
            value = D_800B494C[g_BattlePartyBattlers[battler_index].chr.stats.resistances[RES_INDEX_PSIONIC + 1]];
        }
        if (element_mask & 0x100u) {
            value = D_800B494C[g_BattlePartyBattlers[battler_index].chr.stats.resistances[RES_INDEX_PSIONIC + 2]];
        }
    } else {
        if (element_mask & ELEM_PSIONIC) {
            value = D_800B494C[ENEMY_COMBATANT(battler_index).stats.resistances[RES_INDEX_PSIONIC]];
        }
        if (element_mask & ELEM_STATUS) {
            value = D_800B494C[ENEMY_COMBATANT(battler_index).stats.resistances[RES_INDEX_PSIONIC + 1]];
        }
        if (element_mask & 0x100u) {
            value = D_800B494C[ENEMY_COMBATANT(battler_index).stats.resistances[RES_INDEX_PSIONIC + 2]];
        }
    }

    if ((element_mask & 0x1C0u) == 0) {
        value = 0xFFFF; /* no element selected: -1 once truncated to s16. */
    }
    return value;
}
