#include "area104_14.h"

/* func_801F39EC */
MATCH void Area_StepHudBannerDown(void) {
    SELF(Actor)->screen_y += 0xA;
    if (SELF(Actor)->screen_y >= 0xF0) {
        SELF(Actor)->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        SELF(Actor)->unk_03 = 1;
    }
    Area_DrawHudBanner(92, SELF(Actor)->screen_y);
}
