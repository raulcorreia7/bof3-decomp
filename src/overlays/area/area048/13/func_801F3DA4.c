#include "area048_13.h"

MATCH void func_801F3DA4(void) {
    g_Task->timer = 0;
    if (COORD_INT(g_Task->pos.x) == 0 && SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        func_801F41F0(0, 3);
        g_Task->header.step = 3;
    } else {
        func_801F41F0(COORD_INT(g_Task->pos.x), 0);
        g_Task->header.step = 1;
    }
}
