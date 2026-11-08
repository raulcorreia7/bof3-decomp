#include "area167_13.h"

MATCH void func_801F36FC(void) {
    if (g_AreaSceneMode == 0x10) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
        }
        g_Task->header.step += 1;
    }
    Area_Update();
}
