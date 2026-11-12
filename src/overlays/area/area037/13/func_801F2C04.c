#include "area037_13.h"

MATCH void func_801F2C04(void) {
    Actor* work;
    s32    dx;
    s32    dy;
    u8     cell_index;

    if (g_Task->header.step == 0) {
        g_Task->param.unk_0B = COORD_INT(g_Task->pos.x);
        work                 = g_Task;
        work->pos.x.fixed    = ((D_801F3B34[work->param.unk_0B] - 0x80) << 7) + 0x38;
        work->pos.y.fixed    = (D_801F3B38[work->param.unk_0B] - 0x80) << 7;
        work->pos.z.fixed    = D_801F3B3C[work->param.unk_0B];
        work->header.step += 1;
    }
    if (g_AreaDrawFlags & 0x4) {
        cell_index = g_Task->param.unk_0B;
        dx         = g_AreaTargetCellX;
        dx += 6;
        dx -= D_801F3B34[cell_index];
        if (ABS(dx) < 0xB) {
            dy = g_AreaTargetCellY;
            dy += 6;
            dy -= D_801F3B38[cell_index];
            if (ABS(dy) < 0xB) {
                func_801F2D44();
            }
        }
    }
}
