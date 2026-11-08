#include "area042_13.h"

MATCH void func_801F3B24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(g_Task->pos.x)]) == 0) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
    g_Task->timer += 1;
    if (g_Task->timer >= 0x41U) {
        g_Task->timer = 0;
        if ((RANDOM_MASK(1)) != 0) {
            g_Task->header.step = 5;
        }
    }
}
