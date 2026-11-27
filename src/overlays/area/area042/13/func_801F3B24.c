#include "area042_13.h"

MATCH void func_801F3B24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(SELF(Actor)->pos.x)]) == 0) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 65U) {
        SELF(Actor)->timer = 0;
        if ((RANDOM_MASK(1)) != 0) {
            SELF(Actor)->header.step = 5;
        }
    }
}
