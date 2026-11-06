#include "game_00.h"

MATCH s32 func_801C6EE0(s32 entry_count, s32 pos_x, s32 pos_y, s32 reach) {
    s32             index;
    s32             count;
    s32             probe_reach;
    u8*             fields;
    EncounterEnemy* entry;

    entry       = D_801463DC;
    index       = 0;
    count       = entry_count;
    probe_reach = reach;
    if (count & 0xFF) {
        fields = (u8*)D_801463DC + 8;
    loop_2:
        if (entry->active != 0) {
            u8 slot;

            slot = fields[-7];
            if (!(func_801C7498(pos_x, pos_y, *(s32*)(fields - 4), *(s32*)(fields), probe_reach & 0xFF,
                                ENCOUNTER_ENEMIES[slot].reach) &
                  0xFF)) {
                return 0;
            }
            fields += 0xC;
            goto block_6; /* entry handled, step the counter */
        }
        fields += 0xC;
    block_6:
        index += 1;
        entry++;
        if ((index & 0xFF) >= (u32)(count & 0xFF)) {
            goto block_7; /* walked every requested entry */
        }
        goto loop_2; /* next entry */
    }
block_7:
    return 1;
}
