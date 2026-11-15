#include "area077_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3D24(void) {
    Actor* task;

    PushMatrix();
    task = g_Task;
    if (task->vx == 0xA5) {
        D_800E5502 = 1;
    }
    if (task->vx >= 0x5B) {
        task->pos.x.fixed = D_80146954.x.fixed;
        task->pos.y.fixed = D_80146954.y.fixed;
        task->pos.z.fixed = D_80146954.z.fixed;
    }
    func_801F4220();
    func_801F43C8();
    func_801F462C(&D_800E4800, 0x80, 0x80, 0);
    PopMatrix();
    if (--g_Task->vx == 0) {
        func_80196070();
    }
}
#else
INCLUDE_ASM(func_801F3D24);
#endif
