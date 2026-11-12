#include "area048_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (!SYS_TestFlag(g_SceneEventFlags, 13)) {
        work = g_Task;
        step = 2;
    } else {
        work = g_Task;
        step = 1;
    }
    work->header.mode = step;
    work              = g_Task;
    work->pos.z.fixed = TO_COORD(256);
}
