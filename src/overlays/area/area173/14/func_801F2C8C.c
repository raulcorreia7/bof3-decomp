#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    g_Task->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 128)) {
        g_Task->header.step = 5;
    } else {
        g_Task->header.step++;
    }
}
