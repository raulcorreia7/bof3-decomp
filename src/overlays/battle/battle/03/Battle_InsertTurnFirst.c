#include "battle_03.h"

/* func_801DD26C */
MATCH void Battle_InsertTurnFirst(s8 arg0) {
    volatile u8* b                      = &g_BattleTurnCursor;
    s32          temp                   = b[0] - 1;
    b[0]                                = temp;
    g_BattleTurnOrder[temp & BYTE_MASK] = arg0;
}
