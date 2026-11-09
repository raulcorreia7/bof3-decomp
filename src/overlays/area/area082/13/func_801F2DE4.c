#include "area082_13.h"

MATCH void func_801F2DE4(void) {
    DVECTOR from[2];
    DVECTOR to[2];
    s32     pos[3];
    MATRIX  matrix;

    g_Task->unk_2C -= 1;
    if (g_Task->unk_2C == 0) {
        Area_SetCameraMatrix(&matrix);
        pos[0] = g_Task->pos.x.fixed;
        pos[1] = g_Task->pos.y.fixed;
        pos[2] = g_Task->pos.z.fixed;
        Area_ProjectPoint(pos, from);
        pos[1] += 0x10000;
        Area_ProjectPoint(pos, to);
        g_Task->unk_6C = ratan2(to[0].vy - from[0].vy, to[0].vx - from[0].vx) + 0x400;
        g_Task->unk_2C = 30;
        g_Task->vy     = 0;
        g_Task->header.mode += 1;
    }
}
