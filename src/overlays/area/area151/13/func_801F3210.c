#include "area151_13.h"

MATCH void func_801F3210(void) {
    Actor* scratch;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = (Actor*)g_SpadWork;
        step    = scratch->unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail;
            }
            if (scratch->unk_18 == g_GameContextSeed) {
                goto tail;
            }
        }
        ((Actor*)g_SpadWork)->unk_48 = 2;
        ((Actor*)g_SpadWork)->unk_09 = 8;
        ((Actor*)g_SpadWork)->unk_01 = 4;
    }
tail:
    Area_AddActor();
}
