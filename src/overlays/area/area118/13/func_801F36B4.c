#include "area118_13.h"

MATCH void func_801F36B4(void) {
    u16 count;

    count            = g_Task->screen_y + 0x20;
    g_Task->screen_y = count;
    if ((s16)count >= 0) {
        func_801F33A4();
        if (g_Task->header.step == 2) {
            return;
        }
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x201);
        }
        g_Task->header.step = 1;
    }
    func_801F381C(0);
}
