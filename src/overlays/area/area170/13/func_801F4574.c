#include "area170_13.h"

MATCH void func_801F4574(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 103) != 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
        }
        SELF(Actor)->header.step++;
    }
    func_801F4640(1);
}
