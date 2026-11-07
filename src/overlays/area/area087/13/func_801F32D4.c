#include "area087_13.h"

MATCH void func_801F32D4(void) {
    Actor* scratch;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = g_Task;
        step    = scratch->param.unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (scratch->unk_18 == g_GameContextSeed) {
                goto tail; /* skips the arming stores: run the step only */
            }
        }
        g_Task->unk_48      = 2;
        g_Task->timer       = 8;
        g_Task->header.mode = 4;
    }
tail:
    Area_AddActor();
}
