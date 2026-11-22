#include "area048_13.h"

MATCH void func_801F3DA4(void) {
    TASK(Actor)->timer = 0;
    if (COORD_INT(TASK(Actor)->pos.x) == 0 && SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        func_801F41F0(0, 3);
        TASK(Actor)->header.step = 3;
    } else {
        func_801F41F0(COORD_INT(TASK(Actor)->pos.x), 0);
        TASK(Actor)->header.step = 1;
    }
}
