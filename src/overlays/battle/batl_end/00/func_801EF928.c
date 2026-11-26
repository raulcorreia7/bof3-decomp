#include "batl_end_00.h"

/* The level-ups the party member gains: the stat rows the flag selects, or the level count
 * for flag 0; each gain adds its level-up modifier and a negative total reports no gain. */
MATCH u16 func_801EF928(s32 id, s32 flag) {
    s32 level;
    s32 new_level;
    s32 i;
    s32 exp;
    s32 work;
    s16 delta;

    delta = 0;
    work  = 0;
    i     = 1;
    level = g_Characters[(u8)id].level;
    exp   = g_Characters[(u8)id].exp;
    while ((u8)i < LEVEL_GROWTH_LEVEL_COUNT) {
        work += g_LevelGrowth[(u8)id][(u8)i].exp;
        if (exp < work) {
            break;
        }
        i++;
    }
    new_level = i;

    switch ((u8)flag) {
        case 0:
            if ((u8)new_level - level <= 0) {
                return 0;
            }
            return (u8)new_level - level;
        case 1:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + g_LevelGrowth[(u8)id][(u8)i].hp + (s8)g_Characters[(u8)id].level_up_modifiers[0];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
        case 2:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + g_LevelGrowth[(u8)id][(u8)i].ap + (s8)g_Characters[(u8)id].level_up_modifiers[1];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
        case 3:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + (g_LevelGrowth[(u8)id][(u8)i].power_defense >> 4) + (s8)g_Characters[(u8)id].level_up_modifiers[2];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
        case 4:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + (g_LevelGrowth[(u8)id][(u8)i].power_defense & 0xF) + (s8)g_Characters[(u8)id].level_up_modifiers[3];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
        case 5:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + (g_LevelGrowth[(u8)id][(u8)i].agility_intelligence >> 4) + (s8)g_Characters[(u8)id].level_up_modifiers[4];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
        case 6:
            for (i = level; (u8)i < (u8)new_level; i++) {
                delta = delta + (g_LevelGrowth[(u8)id][(u8)i].agility_intelligence & 0xF) + (s8)g_Characters[(u8)id].level_up_modifiers[5];
            }
            if (delta < 0) {
                return 0;
            }
            return delta;
    }
    return delta;
}
