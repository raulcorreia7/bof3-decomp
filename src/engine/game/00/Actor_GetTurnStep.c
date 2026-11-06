#include "game_00.h"

MATCH s32 Actor_GetTurnStep(s32 selector) {
    s32 field;
    s32 value;

    field = g_Task->direction_08;
    selector &= 0xFF;
    value = field & 0xFF;
    if ((u32)field < selector) {
        field += 8;
        value = field & 0xFF;
    }
    if ((value >= selector + 1) && (selector + 4 >= value)) {
        return -1;
    }
    return 1;
}
