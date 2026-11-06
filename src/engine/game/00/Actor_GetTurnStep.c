#include "game_00.h"

MATCH s32 Actor_GetTurnStep(s32 selector) {
    s32 field;
    s32 value;

    field = g_Task->direction_08;
    selector &= BYTE_MASK;
    value = field & BYTE_MASK;
    if ((u32)field < selector) {
        field += 8;
        value = field & BYTE_MASK;
    }
    if ((value >= selector + 1) && (selector + 4 >= value)) {
        return -1;
    }
    return 1;
}
