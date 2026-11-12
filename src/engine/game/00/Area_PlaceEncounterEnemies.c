#include "game_00.h"

/* func_801C6BB4 */
MATCH bool Area_PlaceEncounterEnemies(void) {
    EncounterEnemy* entry;
    Enemy*          kind;
    s16             index;
    s16             i;
    s16             slot;
    s32             x;
    s32             y;
    s32             tmp;

    entry      = D_801463DC;
    index      = 0;
    D_801CD8C4 = 0;
    do {
        if (entry->active) {
            i    = D_801CD8C8;
            slot = D_801CD8C4 + ((D_801CD8C0 * (D_801CD8C0 - 1)) >> 1);
            y    = s_EncounterEnemyOffsets[slot].y;
            x    = s_EncounterEnemyOffsets[slot].x + TO_COORD(5);
            kind = ENCOUNTER_ENEMIES + entry->id;
            while (i != 0) {
                tmp = x;
                x   = y;
                y   = -tmp;
                i   = (i + 1) & 0x3;
            }
            for (i = 0; i < ENTITY_SPAWN_SEARCH_COUNT; i++) {
                entry->pos.x = g_EncounterOriginX + x + (s_EntitySpawnOffsets[i].dx << 15);
                entry->pos.y = g_EncounterOriginY + y + (s_EntitySpawnOffsets[i].dy << 15);
                if ((func_801C7518(entry->pos.x, entry->pos.y, kind->reach) & BYTE_MASK) && (func_801C6EE0((u8)index, entry->pos.x, entry->pos.y, kind->reach) & BYTE_MASK)) {
                    D_801CD8C4++;
                    break;
                }
            }
            if (i == ENTITY_SPAWN_SEARCH_COUNT) {
                entry->active = 0;
            }
        }
        entry++;
        index++;
    } while (index < 8);
    return D_801CD8C4 != 0;
}
