#include "area152_13.h"

MATCH void func_801F3614(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0xA;
    if ((s16)scratch->unk_30 < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto force;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
force:
    ((u8*)g_SpadWork)[0x03] = 3;
done:
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
