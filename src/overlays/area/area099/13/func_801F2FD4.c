#include "area099_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FD4(void) {
    Actor* task;
    s32    x;
    s32    y;
    s32    vx;
    s32    vy;
    s32    vz;
    u8     mode;

    task              = g_Task;
    x                 = task->pos.x.fixed;
    mode              = task->unk_0A;
    vx                = task->vx;
    vy                = task->vy;
    task->pos.x.fixed = x + vx;
    y                 = task->pos.y.fixed;
    task->unk_0A      = mode - 1;
    task->pos.y.fixed = y + vy;
    COORD_INT(task->pos.z) += task->vz >> 8;
    vz       = task->vz;
    task->vz = vz - 0x700;
    if (vz > 0) {
        if (g_Task->vz < 0) {
            Actor_RequestScript(0x51);
        }
    }
    if (g_Task->unk_0A == 0) {
        g_Task->unk_04 = 0;
    } else {
        FIELD(u16, g_GameState, 0x122) -= 2;
    }
}
#else
INCLUDE_ASM(func_801F2FD4);
#endif
