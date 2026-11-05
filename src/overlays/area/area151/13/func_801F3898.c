#include "area151_13.h"

MATCH void func_801F3898(void) {
    Actor* scratch;
    /* FAKE: value pinned to v0. */
    s32    armed;

    scratch = (Actor*)g_SpadWork;
    scratch->unk_30 += 0xA;
    if ((s16)scratch->unk_30 >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed                        = 1;
        ((Actor*)g_SpadWork)->unk_03 = armed;
    }
    Area_DrawHudBanner(0x5C, ((Actor*)g_SpadWork)->unk_30);
}
