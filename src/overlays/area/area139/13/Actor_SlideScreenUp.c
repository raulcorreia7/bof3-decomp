#include "area139_13.h"

/* func_801F3F14 */
MATCH void Actor_SlideScreenUp(void) {
    Actor* work;

    work = (Actor*)g_Task;
    work->screen_y += 0x20;
    if ((s16)work->screen_y >= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        ((Actor*)g_Task)->header.step = 1;
    }
    Area_Update();
}
