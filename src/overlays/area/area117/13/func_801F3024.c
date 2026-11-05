#include "area117_13.h"

MATCH void func_801F3024(void) {
    u16 position;

    position       = g_Task->unk_30 + 0x20;
    g_Task->unk_30 = position;
    if ((s16)position >= 0) {
        func_801F2E08();
        if (g_Task->step == 2) {
            return;
        }
        g_Task->step = 1;
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x201);
        }
    }
    func_801F314C();
}
