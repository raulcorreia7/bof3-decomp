#include "area042_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C84(void) {
    Actor* task;
    s16    height;
    s32    vz;
    /* FAKE: pure C frames this function 0x10 bytes short. */
    FAKE_STACK_PADS(u8, 0x10);

    height                 = Area_SampleHeight(g_Task->vx, g_Task->vy);
    vz                     = TO_COORD(height) + TO_COORD(0x100);
    task                   = g_Task;
    task->vz               = vz;
    task->gravity          = vz;
    COORD_INT(task->pos.z) = height;
    task->state_70.word    = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
        g_Task->header.mode = 1;
    } else {
        g_Task->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F2C84);
#endif
