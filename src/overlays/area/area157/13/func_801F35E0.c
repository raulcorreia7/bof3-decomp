#include "area157_13.h"

MATCH void func_801F35E0(void) {
    if (g_Task->direction_08 != FACING_UP_LEFT) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(g_Task->pos.y) - 2) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(g_Task->pos.x) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(g_Task->pos.x) + 1) << 16)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(g_Task->pos.x) - 2) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(g_Task->pos.y) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(g_Task->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
                }
                g_Task->header.step++;
            }
        }
    }
}
