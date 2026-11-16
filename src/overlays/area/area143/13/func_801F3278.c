#include "area143_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3278(void) {
    Actor* task;
    s32    z;
    s32    height;
    s32    top;
    s32    bottom;

    task              = g_Task;
    z                 = task->pos.z.fixed;
    height            = z + 8;
    task->pos.z.fixed = height;
    top               = MIN(height, 0x100);

    bottom = z - 0x18;
    if (bottom < 0) {
        bottom = 0;
    }

    func_801F3584(top, bottom, 1);

    if (bottom >= 0x100) {
        task              = g_Task;
        task->pos.z.fixed = 0;
        task->header.step++;
    }
}
#else
INCLUDE_ASM(func_801F3278);
#endif
