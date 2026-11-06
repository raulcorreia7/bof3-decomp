#include "area170_13.h"

MATCH void func_801F4574(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x67) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 0));
        }
        g_Task->header.step++;
    }
    func_801F4640(1);
}
