#include "area157_13.h"

MATCH void func_801F3864(void) {
    Actor* work;

    work = SELF(Actor);
    work->screen_y -= 0x20;
    if (work->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        SELF(Actor)->header.step = 1;
    }
}
