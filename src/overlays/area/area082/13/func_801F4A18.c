#include "area082_13.h"

MATCH void func_801F4A18(void) {
    s32    x_offset = 0x238000;
    s32    y_offset = 0x1B8000;
    Actor* work     = g_Task;
    s32    x;
    s32    y;
    u8     state;

    work->z.fixed = -0x4C0;
    x             = work->vx;
    y             = work->vy;
    state         = work->step + 1;
    work->vz      = 0x53020;
    work->unk_32  = 0;
    work->unk_30  = 0x60;
    work->vy      = 0;
    work->vx      = 0;
    work->x.fixed = ((x + x_offset) >> 9) - 0x4000;
    work->y.fixed = ((y + y_offset) >> 9) - 0x4000;
    work->step    = state;
}
