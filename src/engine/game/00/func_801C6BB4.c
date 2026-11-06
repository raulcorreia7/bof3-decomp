#include "game_00.h"

MATCH s32 func_801C6BB4(void) {
    EncounterEnemy* entry;
    Enemy*          kind;
    s16             index;
    s16             i;
    s16             slot;
    s32             x;
    s32             y;
    s32             tmp;
    s32             off;

    entry      = D_801463DC;
    index      = 0;
    D_801CD8C4 = 0;
    do {
        if (entry->active) {
            i    = D_801CD8C8;
            slot = D_801CD8C4 + ((D_801CD8C0 * (D_801CD8C0 - 1)) >> 1);
            y    = D_801CD620[slot].y;
            x    = D_801CD620[slot].x + 0x50000;
            kind = ENCOUNTER_ENEMIES + entry->id;
            while (i != 0) {
                tmp = x;
                x   = y;
                y   = -tmp;
                i   = (i + 1) & 3;
            }
            for (i = 0; i < 49; i++) {
                off          = i * 2;
                entry->pos.x = D_80143F24 + x + (s_EntitySpawnOffsets[off] << 15);
                entry->pos.y = D_80143F28 + y + (D_801CD5BD[off] << 15);
                if ((func_801C7518(entry->pos.x, entry->pos.y, kind->reach) & BYTE_MASK) &&
                    (func_801C6EE0((u8)index, entry->pos.x, entry->pos.y, kind->reach) & BYTE_MASK)) {
                    D_801CD8C4++;
                    break;
                }
            }
            if (i == 49) {
                entry->active = 0;
            }
        }
        entry++;
        index++;
    } while (index < 8);
    return D_801CD8C4 != 0;
}
