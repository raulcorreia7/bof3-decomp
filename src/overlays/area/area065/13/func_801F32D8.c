#include "area065_13.h"

MATCH void func_801F32D8(void) {
    Actor* scratch;
    u8     step;

    Actor_SetScreenOrigin();
    if (g_GameEntryState != 1) {
        scratch = g_Task;
        step    = scratch->param.unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (scratch->unk_18 == g_GameEntryAreaId) {
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
