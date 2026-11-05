#include "area173_14.h"

MATCH void func_801F3F08(void) {
    Actor* scratch;
    s32    delta;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0x10;
    if ((s16)scratch->unk_30 <= 0) {
        SYS_SetFlag(g_SceneEventFlags, scratch->direction_08);
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        scratch           = g_SpadWork;
        scratch->state_02 = 1;
    }
    if ((s16)g_SpadWork->unk_30 >= 0x80) {
        delta = -2;
    } else {
        delta = -1;
    }
    func_801F3FBC(0, delta);
    func_801F3FBC(1, 1);
}
