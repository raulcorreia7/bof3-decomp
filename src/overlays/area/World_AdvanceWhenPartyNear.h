#ifndef WORLD_ADVANCE_WHEN_PARTY_NEAR_H
#define WORLD_ADVANCE_WHEN_PARTY_NEAR_H

#include "work/area_spad.h"

/* Advance the work state when the party position is inside the work cell. */
static inline void World_AdvanceWhenPartyNear(void) {
    if (g_Task->direction_08 != FACING_UP_LEFT) {
        if (abs(D_80145EC8 - ((((s32)COORD_INT(g_Task->pos.y) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(D_80145EC4 - ((s32)COORD_INT(g_Task->pos.x) << 16)) <= TO_COORD(1) ||
                abs(D_80145EC4 - (((s32)COORD_INT(g_Task->pos.x) + 1) << 16)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)COORD_INT(g_Task->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(D_80145EC8 - ((s32)COORD_INT(g_Task->pos.y) << 16)) <= TO_COORD(1) ||
                abs(D_80145EC8 - (((s32)COORD_INT(g_Task->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    }
}

#endif
