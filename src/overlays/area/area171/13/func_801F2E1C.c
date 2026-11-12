#include "area171_13.h"

MATCH void func_801F2E1C(void) {
    if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(g_Task->pos.x) + 1) << 16) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(g_Task->pos.y) << 16)) <= TO_COORD(1) ||
            abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(g_Task->pos.y) + 1) << 16)) <= TO_COORD(1)) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
            }
            g_Task->header.step++;
        }
    }
    func_801F3070(1);
}
