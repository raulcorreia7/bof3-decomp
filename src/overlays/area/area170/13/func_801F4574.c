#include "area170_13.h"

MATCH void func_801F4574(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 103) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0));
        }
        g_Task->header.step++;
    }
    func_801F4640(1);
}
