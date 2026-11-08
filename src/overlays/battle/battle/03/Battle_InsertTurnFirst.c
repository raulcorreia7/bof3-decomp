#include "battle_03.h"

/* func_801DD26C */
MATCH void Battle_InsertTurnFirst(s8 arg0) {
    volatile u8* b                        = &g_Battle.turn_cursor;
    s32          temp                     = b[0] - 1;
    b[0]                                  = temp;
    g_Battle.turn_order[temp & BYTE_MASK] = arg0;
}
