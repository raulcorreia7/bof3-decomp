#include "boss035_16.h"

MATCH void func_800C190C(void) {
    u16* flags = &g_Battle.state;

    if ((*flags & BATTLE_STATE_WINDOW_BUSY) != 0 && WINDOW_EFFECT_IDLE()) {
        g_AreaDrawFlags = 0;
        *flags &= ~BATTLE_STATE_WINDOW_BUSY;
    }
}
