#include "area141_13.h"

MATCH void func_801F2F14(void) {
    switch (COORD_INT(g_Task->pos.x)) {
        case 0:
            if (SYS_TestFlag(D_80144EF8, 20)) {
                g_Task->header.step++;
            }
            break;
        case 1:
            if (g_AreaSceneMode == 1) {
                g_Task->header.step++;
            }
            break;
        case 2:
            if (SYS_TestFlag(g_SceneEventFlags, 122)) {
                g_Task->header.step++;
            }
            break;
        case 3:
            if (SYS_TestFlag(g_SceneEventFlags, 123)) {
                g_Task->header.step++;
            }
            break;
        case 4:
            if (SYS_TestFlag(g_SceneEventFlags, 124)) {
                g_Task->header.step++;
            }
            break;
    }
}
