#include "area141_13.h"

MATCH void func_801F2F14(void) {
    switch (COORD_INT(SELF(Actor)->pos.x)) {
        case 0:
            if (SYS_TestFlag(g_SceneFlagRows[SCENARIO_DESERT_OF_DEATH], 20)) {
                SELF(Actor)->header.step++;
            }
            break;
        case 1:
            if (g_AreaSceneMode == 1) {
                SELF(Actor)->header.step++;
            }
            break;
        case 2:
            if (SYS_TestFlag(g_SceneEventFlags, 122)) {
                SELF(Actor)->header.step++;
            }
            break;
        case 3:
            if (SYS_TestFlag(g_SceneEventFlags, 123)) {
                SELF(Actor)->header.step++;
            }
            break;
        case 4:
            if (SYS_TestFlag(g_SceneEventFlags, 124)) {
                SELF(Actor)->header.step++;
            }
            break;
    }
}
