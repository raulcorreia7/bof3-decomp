#include "area042_13.h"

MATCH void func_801F3988(void) {
    g_Task->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(g_Task->pos.x)])) {
        Area_SetPosX(3);
        g_Task->header.step = 3;
    } else {
        Area_SetPosX(0);
        g_Task->header.step = 1;
    }
}
