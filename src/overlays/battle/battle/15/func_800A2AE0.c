#include "battle_15.h"

MATCH s16 func_800A2AE0(u8 battler_index, u16 element_mask) {
    s32 result = 0;
    u8  element_slot;

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (element_mask & ELEM_FIRE) {
            element_slot = g_BattlePartyBattlers[battler_index].stats.resistances[0];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_FROST) {
            element_slot = g_BattlePartyBattlers[battler_index].stats.resistances[1];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_ELECTRIC) {
            element_slot = g_BattlePartyBattlers[battler_index].stats.resistances[2];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_EARTH) {
            element_slot = g_BattlePartyBattlers[battler_index].stats.resistances[3];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_WIND) {
            element_slot = g_BattlePartyBattlers[battler_index].stats.resistances[4];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
    } else {
        if (element_mask & ELEM_FIRE) {
            u32 v;
            v            = (u32)(battler_index - 3u);
            element_slot = g_BattleEnemies[0x3F7u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_FROST) {
            u32 v;
            v            = (u32)(battler_index - 3u);
            element_slot = g_BattleEnemies[0x3F8u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_ELECTRIC) {
            u32 v;
            v            = (u32)(battler_index - 3u);
            element_slot = g_BattleEnemies[0x3F9u + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_EARTH) {
            u32 v;
            v            = (u32)(battler_index - 3u);
            element_slot = g_BattleEnemies[0x3FAu + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
        if (element_mask & ELEM_WIND) {
            u32 v;
            v            = (u32)(battler_index - 3u);
            element_slot = g_BattleEnemies[0x3FBu + (((v * 36u) - v) * 8u)];
            result += (s16)D_800B492C[8u + (u32)element_slot];
        }
    }

    return (s16)result;
}
