#include "game_00.h"

MATCH s32 func_801B43D0(s32 x, s32 y, s32 dir) {
    s8  slot;
    s32 diff;

    slot = func_801BDE14(x, y, TASK_BYTES[0x70]);
    if (slot != -1) {
        if ((g_Actors[slot].unk_06 != 8) && (g_Actors[slot].unk_7C != 0xFFFF)) {
            diff = g_Actors[slot].z.part.integer;
            diff -= g_Task->z.part.integer;
            diff = ABS(diff);
            if (diff >= 0x101) {
                slot = -1;
            }
        } else {
            slot = -1;
        }
    }
    return slot & BYTE_MASK;
}
