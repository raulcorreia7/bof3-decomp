#include "area151_13.h"

/* Requests an area restart when the entry changes. */
/* func_801F3210 */
MATCH s32 Area_RequestRestartOnEntryChange(void) {
    Actor* scratch;
    u8     step;

    Actor_SetScreenOrigin();
    if (g_GameEntryState != 1) {
        scratch = SELF(Actor);
        step    = scratch->param.unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail;
            }
            if (scratch->unk_18 == g_GameEntryAreaId) {
                goto tail;
            }
        }
        SELF(Actor)->unk_48      = 2;
        SELF(Actor)->timer       = 8;
        SELF(Actor)->header.mode = 4;
    }
tail:
    Area_AddActor();
}
