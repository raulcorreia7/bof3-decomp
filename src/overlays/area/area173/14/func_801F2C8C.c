#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    TASK(Actor)->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 128)) {
        TASK(Actor)->header.step = 5;
    } else {
        TASK(Actor)->header.step++;
    }
}
