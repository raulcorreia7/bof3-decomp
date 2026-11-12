#include "area151_13.h"

/* func_801F3898 */
MATCH void Area_StepHudBannerDown(void) {
    Actor* scratch;
    /* FAKE: value pinned to v0. */
    s32    armed;

    scratch = g_Task;
    scratch->screen_y += 0xA;
    if ((s16)scratch->screen_y >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed            = 1;
        (g_Task)->unk_03 = armed;
    }
    Area_DrawHudBanner(92, (g_Task)->screen_y);
}
