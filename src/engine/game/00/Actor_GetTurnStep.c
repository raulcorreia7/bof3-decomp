#include "game_00.h"

MATCH s32 Actor_GetTurnStep(s32 target_facing) {
    s32 field;
    s32 value;

    field = g_Task->direction_08;
    target_facing &= BYTE_MASK;
    value = field & BYTE_MASK;
    if ((u32)field < target_facing) {
        field += 8;
        value = field & BYTE_MASK;
    }
    if ((value >= target_facing + 1) && (target_facing + 4 >= value)) {
        return -1;
    }
    return 1;
}
