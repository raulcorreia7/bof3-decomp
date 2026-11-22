#include "batl_end_00.h"

#ifdef NON_MATCHING
NON_MATCHING u16 func_801EF928(u8 id, u8 flag) {
    u8  level;
    u8  new_level;
    u8  final_level;
    u8  i;
    u8  modifier;
    s32 work;
    s32 exp;
    s32 delta;
    s32 level_offset;
    s32 gain;

    delta     = 0;
    work      = 0;
    new_level = 1;
    level     = g_Characters[id].level;
    exp       = g_Characters[id].exp;
    while (new_level < LEVEL_GROWTH_LEVEL_COUNT) {
        work += g_LevelGrowth[id][new_level].exp;
        if (exp < work) {
            break;
        }
        new_level++;
    }
    final_level = new_level;
    switch (flag) {
        case 0:
            if ((u8)final_level - level <= 0) {
                return 0;
            }
            return ((u8)final_level - level) & 0xFFFF;
        case 1:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[0];
                gain         = delta + (&g_LevelGrowth[0][level_offset])[i].hp;
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        case 2:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[1];
                gain         = delta + (&g_LevelGrowth[0][level_offset])[i].ap;
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        case 3:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[2];
                gain         = delta + ((&g_LevelGrowth[0][level_offset])[i].power_defense >> 4);
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        case 4:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[3];
                gain         = delta + ((&g_LevelGrowth[0][level_offset])[i].power_defense & 0xF);
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        case 5:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[4];
                gain         = delta + ((&g_LevelGrowth[0][level_offset])[i].agility_intelligence >> 4);
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        case 6:
            for (i = level; i < final_level; i++) {
                level_offset = id * LEVEL_GROWTH_LEVEL_COUNT;
                modifier     = g_Characters[id].level_up_modifiers[5];
                gain         = delta + ((&g_LevelGrowth[0][level_offset])[i].agility_intelligence & 0xF);
                delta        = (s8)modifier + gain;
            }
            if ((s16)delta < 0) {
                return 0;
            }
            return delta & 0xFFFF;
        default:
            return delta & 0xFFFF;
    }
}

#else
INCLUDE_ASM(func_801EF928);
#endif
