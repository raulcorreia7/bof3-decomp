#include "battle_15.h"

MATCH void func_800A5120(void) {
    u8* state;

    if (!(D_801485B8 & 0x1)) {
        state             = &g_Battle.row_cursor;
        g_Battle.ui_step  = 2;
        g_Battle.ui_state = 0;
        *state &= 0x7F;
    }
}
