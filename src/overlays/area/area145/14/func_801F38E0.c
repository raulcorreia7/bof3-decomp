#include "area145_14.h"

MATCH void func_801F38E0(void) {
    Actor* work;
    u8*    depth_target;
    s32    result;

    work                           = g_Task;
    work->pos.x.fixed              = 0xA0000;
    work->pos.y.fixed              = 0x630000;
    result                         = Area_SampleHeight(work->pos.x.fixed, 0x630000);
    depth_target                   = (u8*)g_Task;
    FIELD(s32, depth_target, 0x3C) = result << 16;
    depth_target[1]++;
}
