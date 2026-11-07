#include "area151_13.h"

MATCH s32 func_801F3210(void) {
    Actor* scratch;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = (Actor*)g_Task;
        step    = scratch->param.unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail;
            }
            if (scratch->unk_18 == g_GameContextSeed) {
                goto tail;
            }
        }
        ((Actor*)g_Task)->unk_48      = 2;
        ((Actor*)g_Task)->timer       = 8;
        ((Actor*)g_Task)->header.mode = 4;
    }
tail:
    Area_AddActor();
}
