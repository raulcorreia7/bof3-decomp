#include "area151_13.h"

MATCH void func_801F3798(void) {
    Actor* scratch;

    scratch = g_Task;
    if (scratch->param.unk_0B == 0) {
        scratch->timer++;
        scratch = g_Task;
        if (scratch->timer >= 0x5A) {
            scratch->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    g_Task->unk_03++;
done:
    Area_DrawHudBanner(0x5C, (g_Task)->screen_y);
}
