#include "battle_15.h"

/* Sets D_80148627 to 2 and increments g_BattleUIState. */
MATCH void func_800A4B08(void) {
    u8* counter;
    u8  value;

    counter    = (u8*)&g_BattleUIState;
    value      = *counter;
    D_80148627 = 2;
    *counter   = value + 1;
}
