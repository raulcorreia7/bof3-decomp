#include "battle_15.h"

/* Sets D_80148597 to 2, g_BattleMessageState to 1 and increments g_Battle.ui_state. */
MATCH void func_800A5300(void) {
    u8* counter;
    u8  value;

    counter              = (u8*)&g_Battle.ui_state;
    D_80148597           = 2;
    value                = *counter;
    g_BattleMessageState = 1;
    *counter             = value + 1;
}
