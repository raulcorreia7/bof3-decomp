#include "area117_13.h"

MATCH void func_801F2E08(void) {
    if (g_AreaSceneMode != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
        }
        g_Task->header.step = 2;
    }

    if (abs(g_Game.members[0].pos.x.fixed - TO_COORD_HALF(2)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x15)) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x16)) <= TO_COORD(1)) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            }
            g_Task->header.step = 2;
        }
    }

    func_801F314C();
}
