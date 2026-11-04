#include "boss025_13.h"

MATCH void func_800C2680(void) {
    u16* flags;
    u8   i;

    BATTLE_RAISE_STATE(BATTLE_STATE_WINDOW_BUSY);
    UI_SetMode(4);
    g_PartySize = D_801FE4E4;
    for (i = 0; i < g_PartySize; i++) {
        D_80144F5D[i] = D_801FE4EC[i];
    }
    g_PartySize = 3;
}
