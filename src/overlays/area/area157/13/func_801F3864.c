#include "area157_13.h"

MATCH void func_801F3864(void) {
    Actor* work;

    work = g_SpadWork;
    work->unk_30 -= 0x20;
    if ((s16)work->unk_30 <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        g_SpadWork->state_02 = 1;
    }
}
