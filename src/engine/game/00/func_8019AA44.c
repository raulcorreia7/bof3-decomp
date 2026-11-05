#include "game_00.h"

MATCH void func_8019AA44(void) {
    Actor* work;
    Vec3i* angle;

    work = g_Task;
    if (work->unk_09 != 0) {
        angle = &D_801481E8;
        angle->x += D_801481F8.x;
        angle->y += D_801481F8.y;
        angle->z += D_801481F8.z;
        g_AreaCameraAngle.vx = (s16)(angle->x >> 16);
        g_AreaCameraAngle.vy = (s16)(angle->y >> 16);
        g_AreaCameraAngle.vz = (s16)(angle->z >> 16);
        work->unk_09--;
        return;
    }
    work->mode = 2;
}
