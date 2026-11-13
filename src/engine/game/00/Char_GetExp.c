#include "game_00.h"

/* func_801ADDD4 */
MATCH void Char_GetExp(s32 char_id) {
    u8  new_level;
    u8  current_level;
    u8  level;
    int tmp;
    s32 work;
    u16 value;
    work      = 0;
    new_level = 1;
    while (new_level < LEVEL_GROWTH_LEVEL_COUNT) {
        work += g_LevelGrowth[(u8)char_id][new_level].exp;
        if ((s32)g_Characters[(u8)char_id].exp < work) {
            break;
        }
        new_level++;
    }

    current_level = g_Characters[(u8)char_id].level;
    if (current_level == LEVEL_GROWTH_LEVEL_COUNT) {
        return;
    }
    if (new_level - current_level <= 0) {
        return;
    }
    level = current_level;
    while (level < new_level) {
        work = g_LevelGrowth[(u8)char_id][level].hp + ((s8)g_Characters[(u8)char_id].level_up_modifiers[0]);
        CLAMP_MIN(work, 0);
        value                                 = g_Characters[(u8)char_id].base.max_hp + work;
        g_Characters[(u8)char_id].base.max_hp = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.max_hp = 999;
        }
        work = g_LevelGrowth[(u8)char_id][level].ap + ((s8)g_Characters[(u8)char_id].level_up_modifiers[1]);
        CLAMP_MIN(work, 0);
        value                                 = g_Characters[(u8)char_id].base.max_ap + work;
        g_Characters[(u8)char_id].base.max_ap = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.max_ap = 999;
        }
        work = (g_LevelGrowth[(u8)char_id][level].power_defense >> 4) + ((s8)g_Characters[(u8)char_id].level_up_modifiers[2]);
        CLAMP_MIN(work, 0);
        value                                = g_Characters[(u8)char_id].base.power + work;
        g_Characters[(u8)char_id].base.power = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.power = 999;
        }
        work = (g_LevelGrowth[(u8)char_id][level].power_defense & 0xF) + ((s8)g_Characters[(u8)char_id].level_up_modifiers[3]);
        CLAMP_MIN(work, 0);
        value                                  = g_Characters[(u8)char_id].base.defense + work;
        g_Characters[(u8)char_id].base.defense = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.defense = 999;
        }
        work = (g_LevelGrowth[(u8)char_id][level].agility_intellect >> 4) + ((s8)g_Characters[(u8)char_id].level_up_modifiers[4]);
        CLAMP_MIN(work, 0);
        value                                  = g_Characters[(u8)char_id].base.agility + work;
        g_Characters[(u8)char_id].base.agility = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.agility = 999;
        }
        tmp  = g_LevelGrowth[(u8)char_id][level].agility_intellect & 0xF;
        work = tmp + ((s8)g_Characters[(u8)char_id].level_up_modifiers[5]);
        CLAMP_MIN(work, 0);
        value                                    = g_Characters[(u8)char_id].base.intellect + work;
        g_Characters[(u8)char_id].base.intellect = value;
        if (value >= 1000) {
            g_Characters[(u8)char_id].base.intellect = 999;
        }
        Char_AddAbility(g_LevelGrowth[(u8)char_id][level].ability, (u8)char_id, 0, 0);
        Char_AddAbility(g_LevelGrowth[(u8)char_id][level].extra_ability, (u8)char_id, 0, 0);
        level++;
    }

    g_Characters[(u8)char_id].level = new_level;
    Char_RebuildStats(&g_Characters[(u8)char_id]);
}
