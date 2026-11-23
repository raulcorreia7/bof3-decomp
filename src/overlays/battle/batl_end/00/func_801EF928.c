#include "batl_end_00.h"

/* The level-ups the party member gains: the stat rows the flag selects, or the level count
 * for flag 0; each gain adds its level-up modifier and a negative total reports no gain. */
#ifdef NON_MATCHING
NON_MATCHING u16 func_801EF928(s32 id, s32 flag) {
    u8  level;
    u8  new_level;
    u8  i;
    s32 modifier;
    s32 exp;
    s32 work;
    s32 delta;

    work      = 0;
    delta     = 0;
    new_level = 1;
    level     = g_Characters[(u8)id].level;
    exp       = g_Characters[(u8)id].exp;
    while (new_level < LEVEL_GROWTH_LEVEL_COUNT) {
        work += g_LevelGrowth[(u8)id][new_level].exp;
        if (exp < work) {
            break;
        }
        new_level++;
    }

    switch ((u8)flag) {
        case 0:
            if ((u8)new_level - level <= 0) {
                return 0;
            }
            return ((u8)new_level - level) & 0xFFFF;
        case 1:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[0];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + g_LevelGrowth[(u8)id][i].hp);
                }
            }
            break;
        case 2:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[1];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + g_LevelGrowth[(u8)id][i].ap);
                }
            }
            break;
        case 3:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[2];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + (g_LevelGrowth[(u8)id][i].power_defense >> 4));
                }
            }
            break;
        case 4:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[3];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + (g_LevelGrowth[(u8)id][i].power_defense & 0xF));
                }
            }
            break;
        case 5:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[4];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + (g_LevelGrowth[(u8)id][i].agility_intelligence >> 4));
                }
            }
            break;
        case 6:
            if (level < new_level) {
                /* FAKE: a plain read folds the cast into lb; retail loads lbu and extends. */
                modifier = ((volatile Character*)g_Characters)[(u8)id].level_up_modifiers[5];
                for (i = level; i < new_level; i++) {
                    delta = (s8)modifier + (delta + (g_LevelGrowth[(u8)id][i].agility_intelligence & 0xF));
                }
            }
            break;
        default:
            return delta & 0xFFFF;
    }
    if ((s16)delta < 0) {
        return 0;
    }
    return delta & 0xFFFF;
}
#else
INCLUDE_ASM(func_801EF928);
#endif
