#include "area152_13.h"

/* func_801F3614 */
MATCH void Area_RaiseHudBanner(void) {
    Actor* scratch;

    scratch = g_Task;
    scratch->screen_y -= 0xA;
    if ((s16)scratch->screen_y < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto force;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
force:
    g_Task->unk_03 = 3;
done:
    Area_DrawHudBanner(92, g_Task->screen_y);
}
