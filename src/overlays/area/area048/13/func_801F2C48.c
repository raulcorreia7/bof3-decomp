#include "area048_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (!SYS_TestFlag(g_SaveData.scene_event_flags, 0xD)) {
        work = g_Task;
        step = 2;
    } else {
        work = g_Task;
        step = 1;
    }
    work->header.mode = step;
    work              = g_Task;
    work->pos.z.fixed = 0x1000000;
}
