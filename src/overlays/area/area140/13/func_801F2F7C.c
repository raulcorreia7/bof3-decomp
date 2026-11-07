#include "area140_13.h"

MATCH void func_801F2F7C(void) {
    Actor* work;

    work = (Actor*)g_Task;
    work->screen_y += 0x20;
    if ((s16)work->screen_y >= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        ((Actor*)g_Task)->header.step = 1;
    }
    func_801F3050();
}
