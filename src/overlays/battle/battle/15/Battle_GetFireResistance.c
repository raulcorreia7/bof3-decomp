#include "battle_15.h"

/* func_800A2AE0 */
MATCH s16 Battle_GetFireResistance(u8 battler_index, u16 element_mask) {
    s32 result = 0;
    u8  element_index;

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (element_mask & ELEM_FIRE) {
            element_index = g_Game.members[battler_index].chr.stats.resistances[0];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_FROST) {
            element_index = g_Game.members[battler_index].chr.stats.resistances[1];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_ELECTRIC) {
            element_index = g_Game.members[battler_index].chr.stats.resistances[2];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_EARTH) {
            element_index = g_Game.members[battler_index].chr.stats.resistances[3];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_WIND) {
            element_index = g_Game.members[battler_index].chr.stats.resistances[4];
            result += (s16)D_800B492C[8u + element_index];
        }
    } else {
        if (element_mask & ELEM_FIRE) {
            u32 v;
            v             = (battler_index - 3u);
            element_index = g_BattleEnemies[0x3F7u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_FROST) {
            u32 v;
            v             = (battler_index - 3u);
            element_index = g_BattleEnemies[0x3F8u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_ELECTRIC) {
            u32 v;
            v             = (battler_index - 3u);
            element_index = g_BattleEnemies[0x3F9u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_EARTH) {
            u32 v;
            v             = (battler_index - 3u);
            element_index = g_BattleEnemies[0x3FAu + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + element_index];
        }
        if (element_mask & ELEM_WIND) {
            u32 v;
            v             = (battler_index - 3u);
            element_index = g_BattleEnemies[0x3FBu + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + element_index];
        }
    }

    return result;
}
