#include "batl_end_00.h"

#ifdef NON_MATCHING
NON_MATCHING u16 func_801EF928(u8 id, u8 flag) {
    u8  level;
    u8  new_level;
    u8  i;
    s8  modifier;
    s32 work;
    s32 exp;
    s32 delta;

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
    switch (flag) {
        case 0:
            if (new_level - level <= 0) {
                return 0;
            }
            return new_level - level;
        case 1:
            modifier = g_Characters[id].level_up_modifiers[0];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].hp;
                delta += modifier;
            }
            break;
        case 2:
            modifier = g_Characters[id].level_up_modifiers[1];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].ap;
                delta += modifier;
            }
            break;
        case 3:
            modifier = g_Characters[id].level_up_modifiers[2];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].power_defense >> 4;
                delta += modifier;
            }
            break;
        case 4:
            modifier = g_Characters[id].level_up_modifiers[3];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].power_defense & 0xF;
                delta += modifier;
            }
            break;
        case 5:
            modifier = g_Characters[id].level_up_modifiers[4];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].agility_intellect >> 4;
                delta += modifier;
            }
            break;
        case 6:
            modifier = g_Characters[id].level_up_modifiers[5];
            for (i = level; i < new_level; i++) {
                delta += g_LevelGrowth[id][i].agility_intellect & 0xF;
                delta += modifier;
            }
            break;
    }
    if ((s16)delta < 0) {
        return 0;
    }
    return delta;
}
#else
INCLUDE_ASM(func_801EF928);
#endif
