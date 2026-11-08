#include "area157_13.h"

MATCH void func_801F3864(void) {
    Actor* work;

    work = g_Task;
    work->screen_y -= 0x20;
    if ((s16)work->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
        }
        g_Task->header.step = 1;
    }
}
