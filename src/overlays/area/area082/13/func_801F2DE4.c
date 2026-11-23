#include "area082_13.h"

MATCH void func_801F2DE4(void) {
    DVECTOR from[2];
    DVECTOR to[2];
    s32     pos[3];
    MATRIX  matrix;

    TASK(Actor)->unk_2C -= 1;
    if (TASK(Actor)->unk_2C == 0) {
        Camera_SetMatrix(&matrix);
        pos[0] = TASK(Actor)->pos.x.fixed;
        pos[1] = TASK(Actor)->pos.y.fixed;
        pos[2] = TASK(Actor)->pos.z.fixed;
        Camera_ProjectPoint(pos, from);
        pos[1] += 0x10000;
        Camera_ProjectPoint(pos, to);
        TASK(Actor)->angle_z = ratan2(to[0].vy - from[0].vy, to[0].vx - from[0].vx) + 0x400;
        TASK(Actor)->unk_2C  = 30;
        TASK(Actor)->vy      = 0;
        TASK(Actor)->header.mode += 1;
    }
}
