#include "area157_13.h"

MATCH void func_801F35E0(void) {
    if (TASK(Actor)->direction != FACING_UP_LEFT) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(TASK(Actor)->pos.y) - 2) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(TASK(Actor)->pos.x) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(TASK(Actor)->pos.x) + 1) << 16)) <= TO_COORD(1)) {
                if (g_GameStateIndex == 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                }
                TASK(Actor)->header.step++;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(TASK(Actor)->pos.x) - 2) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(TASK(Actor)->pos.y) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(TASK(Actor)->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                if (g_GameStateIndex == 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                }
                TASK(Actor)->header.step++;
            }
        }
    }
}
