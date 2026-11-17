#include "boss025_13.h"

MATCH void func_800C1B00(void) {
    u16* flags = &g_Battle.flags;

    if ((*flags & BATTLE_STATE_WINDOW_BUSY) && WINDOW_EFFECT_IDLE()) {
        Battle_ShowActorEntry(0);
        g_AreaDrawFlags = 0;
        *flags &= ~BATTLE_STATE_WINDOW_BUSY;
    }
}
