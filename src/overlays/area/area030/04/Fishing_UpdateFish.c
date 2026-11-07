#include "area030_04.h"

/* Walks the 30 state records (stride 0x98) at g_Actors; for every
 * live record it publishes the record pointer to the scratch work slot
 * g_Task and to g_CurrentActor, dispatches through the handler table
 * g_FishModes with the record's type byte, then rebuilds the record's blend byte
 * 0x5D from flag 0x20 and the signed halfword 0x3E and copies it to 0x5E and
 * 0x5F. */
/* func_801DE4AC */
MATCH void Fishing_UpdateFish(void) {
    void (**table)(void);
    s32 i;
    s32 off;
    s32 base;

    i     = 0;
    table = g_FishModes;
    base  = -0x40;
    off   = 0;
    for (; i < 30; i++, off += 0x98) {
        FishingState* record;
        u8*           cur;

        /* FAKE: retail reads g_Actors as u8[]. */
        if (((u8*)g_Actors)[off] == 0) {
            continue;
        }

        /* FAKE: retail reads g_Actors as u8[]. */
        cur            = &((u8*)g_Actors)[off];
        g_Task         = cur;
        g_CurrentActor = cur;
        table[cur[1]]();

        record = FISHING_STATE;
        if ((record->flags & ACTOR_FLAG_SEMI_TRANSPARENT) != 0) {
            s16 value = record->bounce_3C.half.key_3E;

            if (value > 0) {
                record->tint_5D = base;
            } else if (value < -0x200) {
                record->tint_5D = 0;
            } else {
                record->tint_5D = base - value / 8;
            }
        } else {
            record->tint_5D = 0;
        }

        FISHING_STATE->tint_5E = FISHING_STATE->tint_5D;
        FISHING_STATE->tint_5F = FISHING_STATE->tint_5D;
    }
}
