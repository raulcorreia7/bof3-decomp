#include "area087_13.h"

/* func_801F3784 */
MATCH void Area_RaiseHudBanner(void) {
    g_Task->screen_y -= 0xA;
    if ((s16)g_Task->screen_y < 0xC9) {
        g_Task->unk_03++;
    }

    if ((D_801454F2 != 0 && g_Task->param.unk_0B != 0) || g_GameStateIndex == GAME_REQUEST_MESSAGE || GAME_SCRIPT_ACTIVE() != 0) {
        g_Task->unk_03 = 3;
    }
    Area_DrawHudBanner(92, g_Task->screen_y);
}
