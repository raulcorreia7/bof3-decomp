#include "area151_13.h"

MATCH void func_801F3798(void) {
    Actor* scratch;

    scratch = (Actor*)g_SpadWork;
    if (((u8*)scratch)[0xB] == 0) {
        ((u8*)scratch)[9]++;
        scratch = (Actor*)g_SpadWork;
        if (((u8*)scratch)[9] >= 0x5A) {
            ((u8*)scratch)[0xB]++;
        }
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    ((u8*)g_SpadWork)[3]++;
done:
    Area_DrawHudBanner(0x5C, ((Actor*)g_SpadWork)->unk_30);
}
