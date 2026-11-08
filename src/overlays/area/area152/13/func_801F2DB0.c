#include "area152_13.h"

MATCH void func_801F2DB0(void) {
    s32 x;
    s32 y;
    s32 scaled;
    u8* scratch;

    scaled = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC8 + g_Game.members[0].unk_10 * g_Game.members[0].unk_09) >> 16;

    scratch                 = (u8*)g_Task;
    *(s32*)(scratch + 0x0C) = x;
    *(s32*)(scratch + 0x10) = y;

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

    ((void (**)(void))(D_801F4C3C + 0x11C))[g_Task->header.mode]();
}
