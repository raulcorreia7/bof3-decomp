#include "battle_15.h"

/* Sets D_80148627 to 2, clears D_8014862E and increments g_Battle.ui_state. */
MATCH void func_800A4C44(void) {
    u8* counter = (u8*)&g_Battle.ui_state;
    u8  count   = *counter;

    D_80148627 = 2;
    D_8014862E = 0;
    *counter   = (count + 1);
}
