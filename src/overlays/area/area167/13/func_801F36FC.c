#include "area167_13.h"

MATCH void func_801F36FC(void) {
    if (g_AreaSceneMode == 0x10) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
        }
        SELF(Actor)->header.step += 1;
    }
    Area_Update();
}
