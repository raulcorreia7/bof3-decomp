#include "area048_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (!SYS_TestFlag(g_SceneEventFlags, 0xD)) {
        work = g_SpadWork;
        step = 2;
    } else {
        work = g_SpadWork;
        step = 1;
    }
    work->unk_01 = step;
    work = g_SpadWork;
    work->z.fixed = 0x1000000;
}
