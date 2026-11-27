#include "area118_13.h"

MATCH void func_801F36B4(void) {
    u16 count;

    count                 = SELF(Actor)->screen_y + 0x20;
    SELF(Actor)->screen_y = count;
    if ((s16)count >= 0) {
        func_801F33A4();
        if (SELF(Actor)->header.step == 2) {
            return;
        }
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
        }
        SELF(Actor)->header.step = 1;
    }
    func_801F381C(0);
}
