#include "game_00.h"

MATCH s32 func_801B4150(void) {
    s32 x;
    s32 y;
    s32 slot;
    s32 first;
    u8  dir;

    dir = g_Task->direction_08;
    if (!(dir & 0x1)) {
        first = func_801B43D0(g_Task->pos.x.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].x, g_Task->pos.y.fixed + g_FacingSteps[(u8)(dir - 1) & 0x7].y, (dir - 1) & 0x7);
        first = (s8)first;
        if (first != -1) {
            g_Task->direction_08 = (g_Task->direction_08 - 1) & 0x7;
            return first;
        }
        slot = func_801B43D0(g_Task->pos.x.fixed + g_FacingSteps[(u8)(g_Task->direction_08 + 1) & 0x7].x, g_Task->pos.y.fixed + g_FacingSteps[(u8)(g_Task->direction_08 + 1) & 0x7].y,
                             (g_Task->direction_08 + 1) & 0x7);
        slot = (s8)slot;
        if (slot != first) {
            g_Task->direction_08 = (g_Task->direction_08 + 1) & 0x7;
            return slot;
        }
        dir = g_Task->direction_08;
        return (s8)func_801B43D0(g_Task->pos.x.fixed + g_FacingSteps[dir].x, g_Task->pos.y.fixed + g_FacingSteps[dir].y, dir);
    } else {
        s32 step = g_Task->state_70.byte + 2;
        x        = g_Task->pos.x.fixed + g_FacingSteps[dir].x * step;
        y        = g_Task->pos.y.fixed + g_FacingSteps[dir].y * step;
        if ((Area_GetCellCode((x >> 16), (y >> 16)) & BYTE_MASK) != 0x30) {
            dir = g_Task->direction_08;
            x   = g_Task->pos.x.fixed + g_FacingSteps[dir].x;
            y   = g_Task->pos.y.fixed + g_FacingSteps[dir].y;
        } else if (g_Task->state_70.byte == 0) {
            dir = g_Task->direction_08;
            x += g_FacingSteps[dir].x;
            y += g_FacingSteps[dir].y;
        }
    }
    return (s8)func_801B43D0(x, y, g_Task->direction_08);
}
