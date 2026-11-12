#include "area148_13.h"

MATCH void func_801F36A0(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 90) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x08));
        }
        (g_Task)->header.step += 1;
    }
    func_801F37B8(0, 1);
    func_801F37B8(1, 1);
}
