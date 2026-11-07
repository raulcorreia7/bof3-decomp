#include "area171_13.h"

MATCH void func_801F3000(void) {
    Actor* work;

    work = g_Task;
    work->screen_y -= 0x10;
    if ((s16)work->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        g_Task->header.step = 1;
    }
    func_801F3070(0);
}
