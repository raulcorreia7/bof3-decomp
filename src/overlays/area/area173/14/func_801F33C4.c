#include "area173_14.h"

MATCH void func_801F33C4(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x81)) {
        g_Task->step = 6;
    } else {
        g_AreaSceneMode = 3;
        g_Task->step++;
    }
}
