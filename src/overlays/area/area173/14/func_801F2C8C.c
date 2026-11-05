#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    g_Task->unk_09 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x80)) {
        g_Task->step = 5;
    } else {
        g_Task->step++;
    }
}
