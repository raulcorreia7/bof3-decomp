#include "area118_13.h"

MATCH void func_801F4150(void) {
    s16 distance;
    s32 y;

    g_Task->param.unk_0B     = COORD_INT(g_Task->pos.x);
    g_Task->pos.x.fixed      = (s32)D_801F51B0[g_Task->param.unk_0B * 2] << 16;
    y                        = (s32)D_801F51B1[g_Task->param.unk_0B * 2] << 16;
    g_Task->pos.y.fixed      = y;
    distance                 = Area_SampleHeight(g_Task->pos.x.fixed, y);
    COORD_INT(g_Task->pos.z) = -distance / 2 - D_801F51B4[g_Task->param.unk_0B];
    g_Task->param.unk_0B++;
    if (SYS_TestFlag(D_80144ED0, D_801F5198[g_Task->param.unk_0B]) != 0) {
        g_Task->header.step++;
        func_801F4278();
    } else {
        g_Task->header.step = 3;
        func_801F43FC();
    }
}
