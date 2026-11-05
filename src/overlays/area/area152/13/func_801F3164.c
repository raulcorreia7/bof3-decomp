#include "area152_13.h"

MATCH void func_801F3164(void) {
    u8* scratch;
    u8  step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = (u8*)g_SpadWork;
        step    = scratch[0x0B];
        if (step == scratch[7] && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (*(u32*)(scratch + 0x18) == g_GameContextSeed) {
                goto tail; /* skips the arming stores: run the step only */
            }
        }
        g_SpadWork->unk_48 = 2;
        g_SpadWork->unk_09 = 8;
        g_SpadWork->unk_01 = 4;
    }
tail:
    Area_AddActor();
}
