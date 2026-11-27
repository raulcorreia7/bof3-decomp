#include "area140_13.h"

MATCH void func_801F2F7C(void) {
    Actor* work;

    work = SELF(Actor);
    work->screen_y += 0x20;
    if ((s16)work->screen_y >= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        SELF(Actor)->header.step = 1;
    }
    func_801F3050();
}
