#ifndef WORLD_ADVANCE_WHEN_PARTY_NEAR_H
#define WORLD_ADVANCE_WHEN_PARTY_NEAR_H

#include "area/spad.h"

/* Advance the work state when the party position is inside the work cell. */
static inline void World_AdvanceWhenPartyNear(void) {
    if (g_Task->direction_08 != FACING_UP_LEFT) {
        if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(g_Task->pos.y) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(g_Task->pos.x))) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(g_Task->pos.x) + 1)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(g_Task->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y))) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y) + 1)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    }
}

#endif
