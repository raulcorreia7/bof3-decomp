#include "area104_14.h"

/* func_801F39EC */
MATCH void Area_StepHudBannerDown(void) {
    g_Task->screen_y += 0xA;
    if ((s16)g_Task->screen_y >= 0xF0) {
        g_Task->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        g_Task->unk_03 = 1;
    }
    Area_DrawHudBanner(92, g_Task->screen_y);
}
