#include "area140_13.h"

MATCH void func_801F2FEC(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 84) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
        }
        g_Task->header.step = 2;
    }
    func_801F3050();
}
