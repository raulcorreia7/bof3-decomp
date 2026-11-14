#include "start_08.h"

MATCH void Menu_ExitCamp(void) {
    u16* count;
    u8   i;

    if (WINDOW_EFFECT_IDLE()) {
        for (i = 0; i < CHARACTER_COUNT; i++) {
            func_801E7210(i);
            Char_RebuildStats(&g_Characters[i]);
        }
        if (D_801ED7EC != 0) {
            count               = &g_GameEntryState;
            g_GameEntrySubstate = 0;
            (*count)++;
        } else {
            SYS_ThreadReplace(Game_UpdateMain);
        }
        g_MenuStep.state = 0;
        D_80148653       = 0;
        D_80148655       = 0;
    }
}
