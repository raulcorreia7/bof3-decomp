#include "area048_13.h"

MATCH void func_801F3F98(void) {
    if (((COORD_INT(g_Task->pos.x) == 0) && (SYS_TestFlag(g_SceneEventFlags, 13) == 0)) || ((COORD_INT(g_Task->pos.x) != 0) && (D_8014686B == 0))) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
    g_Task->timer += 1;
    if (g_Task->timer >= 65U) {
        g_Task->timer = 0;
        if (RANDOM_MASK(1)) {
            g_Task->header.step = 5;
        }
    }
    func_801F4258(COORD_INT(g_Task->pos.x));
}
