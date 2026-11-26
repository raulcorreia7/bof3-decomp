#include "area141_13.h"

MATCH void func_801F2F14(void) {
    switch (COORD_INT(TASK(Actor)->pos.x)) {
        case 0:
            if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 20)) {
                TASK(Actor)->header.step++;
            }
            break;
        case 1:
            if (g_AreaSceneMode == 1) {
                TASK(Actor)->header.step++;
            }
            break;
        case 2:
            if (SYS_TestFlag(g_SceneEventFlags, 122)) {
                TASK(Actor)->header.step++;
            }
            break;
        case 3:
            if (SYS_TestFlag(g_SceneEventFlags, 123)) {
                TASK(Actor)->header.step++;
            }
            break;
        case 4:
            if (SYS_TestFlag(g_SceneEventFlags, 124)) {
                TASK(Actor)->header.step++;
            }
            break;
    }
}
