#include "area173_14.h"

MATCH void func_801F3F08(void) {
    Actor* scratch;
    s32    delta;

    scratch = g_Task;
    scratch->screen_y -= 0x10;
    if ((s16)scratch->screen_y <= 0) {
        SYS_SetFlag(g_SceneEventFlags, scratch->direction_08);
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
        }
        scratch              = g_Task;
        scratch->header.step = 1;
    }
    if ((s16)g_Task->screen_y >= 0x80) {
        delta = -2;
    } else {
        delta = -1;
    }
    func_801F3FBC(0, delta);
    func_801F3FBC(1, 1);
}
