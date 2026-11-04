#include "area088_13.h"

MATCH void func_801F448C(void) {
    Actor* scratch;
    s32    armed;

    scratch = g_SpadWork;
    scratch->unk_30 += 0xA;
    if ((s16)scratch->unk_30 >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed              = 1;
        g_SpadWork->unk_03 = armed;
    }
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
