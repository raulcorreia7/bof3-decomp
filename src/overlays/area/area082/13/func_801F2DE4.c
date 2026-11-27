#include "area082_13.h"

MATCH void func_801F2DE4(void) {
    DVECTOR from[2];
    DVECTOR to[2];
    s32     pos[3];
    MATRIX  matrix;

    SELF(Actor)->unk_2C -= 1;
    if (SELF(Actor)->unk_2C == 0) {
        Camera_SetMatrix(&matrix);
        pos[0] = SELF(Actor)->pos.x.fixed;
        pos[1] = SELF(Actor)->pos.y.fixed;
        pos[2] = SELF(Actor)->pos.z.fixed;
        Camera_ProjectPoint(pos, from);
        pos[1] += 0x10000;
        Camera_ProjectPoint(pos, to);
        SELF(Actor)->angle_z = ratan2(to[0].vy - from[0].vy, to[0].vx - from[0].vx) + 0x400;
        SELF(Actor)->unk_2C  = 30;
        SELF(Actor)->vy      = 0;
        SELF(Actor)->header.mode += 1;
    }
}
