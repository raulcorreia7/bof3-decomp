#include "battle_15.h"

/* g_BattleChoicePanel byte 0x0B is the panel page base. */

MATCH void func_80096FBC(void) {
    u32 flags;
    u8  stage;
    u8  message_slot;

    D_801EB4D8[1] = 4;
    func_80097EC0();
    flags = *(u32*)((D_801EB4D8 + 0x10));
    if (flags & 2) {
        if (!(flags & 0x20000)) {
            D_8014857B = 2u;
        }
    }
    stage           = g_BattleUIStep;
    message_slot    = g_BattleMessageSlot[5];
    g_BattleUIState = 0u;
    g_BattleUIStep  = (stage + 1u);
    D_80148656      = message_slot;
}
