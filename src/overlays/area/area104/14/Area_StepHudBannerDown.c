#include "area104_14.h"

/* func_801F39EC */
MATCH void Area_StepHudBannerDown(void) {
    TASK(Actor)->screen_y += 0xA;
    if ((s16)TASK(Actor)->screen_y >= 0xF0) {
        TASK(Actor)->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        TASK(Actor)->unk_03 = 1;
    }
    Area_DrawHudBanner(92, TASK(Actor)->screen_y);
}
