#include "area151_13.h"

/* func_801F36C0 */
MATCH void Area_RaiseHudBanner(void) {
    Actor* scratch;

    scratch = (Actor*)g_Task;
    scratch->screen_y -= 0xA;
    if ((s16)scratch->screen_y < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && TASK_BYTES[0x0B] != 0) {
        goto force;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
force:
    TASK_BYTES[0x03] = 3;
done:
    Area_DrawHudBanner(0x5C, ((Actor*)g_Task)->screen_y);
}
