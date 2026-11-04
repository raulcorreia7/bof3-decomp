#include "area087_13.h"

MATCH void func_801F3784(void) {
    g_SpadWork->unk_30 -= 0xA;
    if ((s16)g_SpadWork->unk_30 < 0xC9) {
        g_SpadWork->unk_03++;
    }

    if ((D_801454F2 != 0 && g_SpadWork->unk_0B != 0) || g_GameStateIndex == GAME_REQUEST_MESSAGE ||
        GAME_SCRIPT_ACTIVE() != 0) {
        g_SpadWork->unk_03 = 3;
    }
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
