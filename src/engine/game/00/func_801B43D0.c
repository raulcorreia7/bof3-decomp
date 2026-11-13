#include "game_00.h"

MATCH s32 func_801B43D0(s32 x, s32 y, s32 dir) {
    s8  slot;
    s32 diff;

    slot = Actor_FindInRange(x, y, g_Task->state_70.byte);
    if (slot != -1) {
        if ((g_Actors[slot].unk_06 != 8) && (g_Actors[slot].unk_7C != 0xFFFF)) {
            diff = COORD_INT(g_Actors[slot].pos.z);
            diff -= COORD_INT(g_Task->pos.z);
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
