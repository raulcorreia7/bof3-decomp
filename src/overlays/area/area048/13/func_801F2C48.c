#include "area048_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (!SYS_TestFlag(g_SceneEventFlags, 0xD)) {
        work = g_Task;
        step = 2;
    } else {
        work = g_Task;
        step = 1;
    }
    work->mode    = step;
    work          = g_Task;
    work->z.fixed = 0x1000000;
}
