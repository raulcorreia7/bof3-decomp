#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    SELF(Actor)->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 128)) {
        SELF(Actor)->header.step = 5;
    } else {
        SELF(Actor)->header.step++;
    }
}
