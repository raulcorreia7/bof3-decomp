#include "area165_13.h"

MATCH void func_801F3518(void) {
    u16 screen_y;

    screen_y              = SELF(Actor)->screen_y - 0x10;
    SELF(Actor)->screen_y = screen_y;
    if ((screen_y << 0x10) <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        SELF(Actor)->header.step += 1;
    }
    Area_Update();
}
