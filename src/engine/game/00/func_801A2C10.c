#include "game_00.h"

MATCH u8 func_801A2C10(void* record) {
    u8  value;
    s16 next;

    value = g_Task->direction_08 & 7;
    next  = (((s32 (*)(s32))rand)(0x80) & 7) | 1;
    if (value != next) {
        g_Task->direction_08 = next;
        FIELD(u8, record, 0x74u) |= 8;
    }
    return g_Task->direction_08;
}
