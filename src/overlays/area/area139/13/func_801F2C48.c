#include "area139_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (D_80143F03 == 2 && !SYS_TestFlag(g_SceneEventFlags, 0x5C)) {
        work = g_SpadWork;
        step = 1;
    } else if (D_80143F03 == 3 && SYS_TestFlag(g_SceneEventFlags, 0x5D)) {
        work = g_SpadWork;
        step = 2;
    } else {
        work = g_SpadWork;
        step = 3;
    }
    work->unk_01 = step;
}
