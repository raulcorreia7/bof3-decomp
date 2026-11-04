#include "area082_13.h"

MATCH void func_801F4A18(void) {
    s32 x_offset = 0x238000;
    s32 y_offset = 0x1B8000;
    Actor* work = g_SpadWork;
    s32 x;
    s32 y;
    u8 state;

    work->z.fixed = -0x4C0;
    x = work->unk_0C;
    y = work->unk_10;
    state = work->state_02 + 1;
    work->vz = 0x53020;
    work->unk_32 = 0;
    work->unk_30 = 0x60;
    work->unk_10 = 0;
    work->unk_0C = 0;
    work->x.fixed = ((x + x_offset) >> 9) - 0x4000;
    work->y.fixed = ((y + y_offset) >> 9) - 0x4000;
    work->state_02 = state;
}
