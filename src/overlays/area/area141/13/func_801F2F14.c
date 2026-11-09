#include "area141_13.h"

MATCH void func_801F2F14(void) {
    switch (COORD_INT(g_Task->pos.x)) {
        case 0:
            if (SYS_TestFlag(D_80144EF8, 0x14)) {
                g_Task->header.step++;
            }
            break;
        case 1:
            if (g_AreaSceneMode == 1) {
                g_Task->header.step++;
            }
            break;
        case 2:
            if (SYS_TestFlag(g_SceneEventFlags, 0x7A)) {
                g_Task->header.step++;
            }
            break;
        case 3:
            if (SYS_TestFlag(g_SceneEventFlags, 0x7B)) {
                g_Task->header.step++;
            }
            break;
        case 4:
            if (SYS_TestFlag(g_SceneEventFlags, 0x7C)) {
                g_Task->header.step++;
            }
            break;
    }
}
