#include "area042_13.h"

MATCH void func_801F3988(void) {
    SELF(Actor)->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(SELF(Actor)->pos.x)])) {
        Area_SetPosX(3);
        SELF(Actor)->header.step = 3;
    } else {
        Area_SetPosX(0);
        SELF(Actor)->header.step = 1;
    }
}
