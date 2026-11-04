#include "area088_13.h"

MATCH void func_801F42B4(void) {
    g_SpadWork->unk_30 -= 0xA;
    if ((s16)g_SpadWork->unk_30 < 0xC9) {
        g_SpadWork->unk_03++;
    }

    if (D_801454F2 != 0 && g_SpadWork->unk_0B != 0) {
        goto force;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
force:
    g_SpadWork->unk_03 = 3;
done:
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
