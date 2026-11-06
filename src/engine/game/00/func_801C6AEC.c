#include "game_00.h"

MATCH s32 func_801C6AEC(s32 candidate_id) {
    s32             slot;
    s32             index;
    s32             kept;
    s32             id_table;
    EncounterEnemy* entry;
    u8              id;

    id_table = candidate_id;
    kept     = 0;
    entry    = D_801463DC;
    index    = 0;
    do {
        slot      = index & BYTE_MASK;
        id        = *(u8*)(id_table + slot);
        entry->id = id;
        if (id != GAME_NONE) {
            if ((RANDOM_MASK(0xF) + 1) <= s_EntitySpawnChances[slot]) {
                entry->active = 1;
                kept += 1;
            } else {
                entry->active = 0;
            }
        } else {
            entry->active = 0;
        }
        index += 1;
        entry++;
    } while ((index & BYTE_MASK) < 8U);
    return kept & BYTE_MASK;
}
