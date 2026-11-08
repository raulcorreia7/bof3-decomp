#include "battle_15.h"

void Battle_AddEnemy(s32 entry_index, s32 enemy_index, s32 entry_value);

MATCH void Battle_LoadEncounterEnemies(void) {
    u8* entries;
    u8  value;
    s32 slot;
    s32 count;

    g_Battle.enemy_count = 0;
    entries              = (u8*)(0x800E4000u + D_801CD78E[g_Battle.encounter * 4u] * 9u);
    slot                 = 0;
    count                = 0;

    do {
        value = entries[slot & BYTE_MASK];
        if (value != 0xFFu) {
            (void)Battle_AddEnemy(slot & BYTE_MASK, count & BYTE_MASK, value);
            count++;
        }
        slot++;
    } while ((slot & BYTE_MASK) < 8u);

    g_Battle.living_enemy_count = g_Battle.enemy_count;
}
