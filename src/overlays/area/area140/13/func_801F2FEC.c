#include "area140_13.h"

MATCH void func_801F2FEC(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 84) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
        }
        SELF(Actor)->header.step = 2;
    }
    func_801F3050();
}
