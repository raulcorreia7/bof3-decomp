#include "game_00.h"

MATCH void func_801B6AB0(void) {
    s32 x;

    x = g_Task->pos.x.fixed;
    if ((((x & 0x7FFF) != 0) || ((g_Task->pos.y.fixed & 0x7FFF) != 0)) && ((g_Task->active_flags & 0x20) == 0)) {
        g_Task->pos.x.fixed      = (x + 0x4800) & ~0x7FFF;
        g_Task->pos.y.fixed      = (g_Task->pos.y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(g_Task->pos.z) = Area_ReadStepHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->direction_08);
        Actor_RequestScript((g_Task->direction_08 + 8) & 0xFF);
        if (((g_Task->pos.x.fixed & 0x7FFF) == 0) && ((g_Task->pos.y.fixed & 0x7FFF) == 0)) {
            Actor_RequestScript(g_Task->direction_08);
        }
    } else {
        Actor_ClearVelocity();
        g_Task->unk_03++;
        func_801B6BC8();
    }
}
