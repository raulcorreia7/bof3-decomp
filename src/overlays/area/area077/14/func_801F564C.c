#include "area077_14.h"

MATCH void func_801F564C(void) {
    TASK(Actor)->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 7)) {
        TASK(Actor)->header.step = 3;
    } else {
        Area_PaletteCopyRow(3, 0, 3, 3);
        TASK(Actor)->header.step++;
    }
}
