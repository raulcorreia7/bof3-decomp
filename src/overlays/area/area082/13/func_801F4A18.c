#include "area082_13.h"

MATCH s32 func_801F4A18(void) {
    s32    x_offset = TO_COORD(35) + COORD_HALF;
    s32    y_offset = TO_COORD(27) + COORD_HALF;
    Actor* work     = g_Task;
    s32    x;
    s32    y;
    u8     state;

    work->pos.z.fixed = -0x4C0;
    x                 = work->vx;
    y                 = work->vy;
    state             = work->header.step + 1;
    work->vz          = 340000;
    work->unk_32      = 0;
    work->screen_y    = 96;
    work->vy          = 0;
    work->vx          = 0;
    work->pos.x.fixed = ((x + x_offset) >> 9) - 0x4000;
    work->pos.y.fixed = ((y + y_offset) >> 9) - 0x4000;
    work->header.step = state;
}
