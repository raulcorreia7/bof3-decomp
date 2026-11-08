#include "area152_13.h"

/* func_801F3164 */
MATCH void Area_RequestRestartOnContextChange(void) {
    u8* scratch;
    u8  step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = (u8*)g_Task;
        step    = scratch[0x0B];
        if (step == scratch[7] && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (*(u32*)(scratch + 0x18) == g_GameContextSeed) {
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
