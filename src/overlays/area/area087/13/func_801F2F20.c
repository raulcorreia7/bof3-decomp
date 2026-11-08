#include "area087_13.h"

MATCH void func_801F2F20(void) {
    s32    x;
    s32    y;
    s32    scaled;
    Actor* scratch;

    scaled = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC8 + g_Game.members[0].unk_10 * g_Game.members[0].unk_09) >> 16;

    scratch     = g_Task;
    scratch->vx = x;
    scratch->vy = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {
        g_Task->param.unk_0B = 1;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {
        g_Task->param.unk_0B = 2;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {
        g_Task->param.unk_0B = 3;
    } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        g_Task->param.unk_0B = 4;
    } else {
        g_Task->param.unk_0B = 0;
    }

    D_801F5734[g_Task->header.mode]();
}
