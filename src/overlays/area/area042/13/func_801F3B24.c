#include "area042_13.h"

MATCH void func_801F3B24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(TASK(Actor)->pos.x)]) == 0) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 65U) {
        TASK(Actor)->timer = 0;
        if ((RANDOM_MASK(1)) != 0) {
            TASK(Actor)->header.step = 5;
        }
    }
}
