#include "game_00.h"

MATCH void func_8019AA44(void) {
    Actor*   work;
    Point3l* angle;

    work = g_Task;
    if (work->timer != 0) {
        angle = &D_801481E8;
        angle->x += D_801481F8.x;
        angle->y += D_801481F8.y;
        angle->z += D_801481F8.z;
        g_AreaCameraAngle.vx = (angle->x >> 16);
        g_AreaCameraAngle.vy = (angle->y >> 16);
        g_AreaCameraAngle.vz = (angle->z >> 16);
        work->timer--;
        return;
    }
    work->header.mode = 2;
}
