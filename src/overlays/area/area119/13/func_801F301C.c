#include "area119_13.h"

MATCH void func_801F301C(void) {
    if (g_AreaSceneMode != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
        }
        g_Task->header.step = 2;
    }

    if (abs(g_Game.members[0].pos.x.fixed - TO_COORD_HALF(0x42)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x3E)) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x3F)) <= TO_COORD(1)) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            }
            g_Task->header.step = 2;
        }
    }

    func_801F3324();
}
