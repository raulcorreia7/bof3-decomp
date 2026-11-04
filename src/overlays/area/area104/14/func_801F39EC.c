#include "area104_14.h"

MATCH void func_801F39EC(void) {
    g_SpadWork->unk_30 += 0xA;
    if ((s16)g_SpadWork->unk_30 >= 0xF0) {
        g_SpadWork->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        g_SpadWork->unk_03 = 1;
    }
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
