#include "battle_15.h"

/* Sets D_80148627 to 2, D_8014862E to 1 and increments g_BattleUIState. */
MATCH void func_800A59E8(void) {
    u8* counter = (u8*)&g_BattleUIState;
    u8  value;

    D_80148627 = 2;
    value      = *counter;
    D_8014862E = 1;
    *counter   = value + 1;
}
