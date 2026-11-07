#include "area119_13.h"

MATCH void func_801F3210(void) {
    u16 position;

    position         = g_Task->screen_y + 0x20;
    g_Task->screen_y = position;
    if ((s16)position >= 0) {
        func_801F301C();
        if (g_Task->header.step == 2) {
            return;
        }
        g_Task->header.step = 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x201);
        }
    }
    func_801F3324();
}
