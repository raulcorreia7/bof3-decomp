#include "start_08.h"

MATCH void Camp_EnterMainLoop(void) {
    u16* count;
    u8   i;

    if (WINDOW_EFFECT_IDLE()) {
        for (i = 0; i < 8; i++) {
            func_801E7210(i);
            Char_RebuildStats(&g_Characters[i]);
        }
        if (D_801ED7EC != 0) {
            count               = &g_GameEntryState;
            g_GameEntrySubstate = 0;
            (*count)++;
        } else {
            CallbackReplace(Game_RunMainLoop);
        }
        D_80148652 = 0;
        D_80148653 = 0;
        D_80148655 = 0;
    }
}
