#include "area087_13.h"

/* func_801F3784 */
MATCH void Area_RaiseHudBanner(void) {
    SELF(Actor)->screen_y -= 0xA;
    if (SELF(Actor)->screen_y < 0xC9) {
        SELF(Actor)->unk_03++;
    }

    if ((D_801454F2 != 0 && SELF(Actor)->param.unk_0B != 0) || g_GameStateIndex == GAME_REQUEST_MESSAGE || GAME_SCRIPT_ACTIVE() != 0) {
        SELF(Actor)->unk_03 = 3;
    }
    Area_DrawHudBanner(92, SELF(Actor)->screen_y);
}
