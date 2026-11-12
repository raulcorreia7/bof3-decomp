#include "area173_14.h"

MATCH void func_801F33C4(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 129)) {
        g_Task->header.step = 6;
    } else {
        g_AreaSceneMode = 3;
        g_Task->header.step++;
    }
}
